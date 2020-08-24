/*****EXTERNAL SECTOR*****/


EQUATION("External_Income")
/*
Nominal value of external income.
*/
	v[0]=VL("External_Income",1);
	v[1]=V("annual_period");
	v[2]= fmod((double) t,v[1]);                				//divides the time period by annual adjustment period (adjust annualy)
	if(v[2]==0)                               					//if the rest of the division is zero (adjust external income)
		{
		v[3]=VL("Annual_Growth", 1);							//nominal growth in the last year
		v[4]=norm(v[3], abs(v[3]));								//random draw from a normal distribution with average equals to past growth and standard deviation equals to past growth in absolute value
		v[5]=V("external_income_growth");						//exogenous parameter that amplifies external growth
		v[6]=(1+v[5]*v[4])*v[0];							  	//current external nominal income will be past income plus random growth
		
		v[7]=V("begin_external_shock");          				//defines when the shock happens
		v[8]=V("duration_external_shock");       				//defines how long the shock lasts
		v[9]=V("size_external_shock");           				//defines the size, in percentage, of the shock
		if(t>=v[7]&&t<v[7]+v[8])
			v[10]=v[6]*(1-v[9]);
		else
			v[10]=v[6];
		}
	else														//if it is not annual period
		v[10]=v[0];												//use last period income
RESULT(max(0,v[10]))


EQUATION("Trade_Balance")
/*
The trade balance is obtained by the difference between total exports and total imports.
*/
	v[0]=V("Total_Exports");
	v[1]=V("Total_Imports");
	v[2]=v[0]-v[1];
RESULT(v[2])


EQUATION("International_Reserves")
/*
The stock of foreign exchange in the period will be calculated by adding to the stock of the past period the current balance of payments (in this case, only the trade balance)
*/
	v[0]=VL("International_Reserves", 1);
	v[1]=V("Trade_Balance");
	v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Exchange_Rate")
/*
Nominal exchange rate.
*/
	v[0]=VL("Exchange_Rate",1);
	v[2]=VL("International_Reserves",1);
	if(v[2]<0)
		{
		v[3]=V("exchange_rate_growth");
		v[4]=(1+v[3])*v[0];
		}
	else
		v[4]=v[0];
RESULT(v[4])
