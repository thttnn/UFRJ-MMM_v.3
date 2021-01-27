/*****EXTERNAL SECTOR*****/


EQUATION("External_Income")
/*
Nominal value of external income.
*/
	v[0]=CURRENT;
	//v[1]=V("annual_period");
	//v[2]=fmod((double) t,v[1]);                					//divides the time period by annual adjustment period (adjust annualy)
	//if(v[2]==0)                               					//if the rest of the division is zero (adjust external income)
	//	{
		v[3]=V("external_income_growth");						//fixed external income growth
		v[4]=V("external_income_sd");							//fixed external income sd
		
		v[6]=VL("Country_Annual_Growth", 1);					//nominal growth in the last year
		v[7]=V("external_income_adjustmnent");                  //exogenous parameter that amplifies external growth based on domestic growth
		v[8]=1+norm((v[3]+v[6]*v[7]), v[4]);					//random draw from a normal distribution with average equals to past growth and standard deviation equals to past growth in absolute value
		
		v[9]=V("external_shock_begin");          				//defines when the shock happens
		v[10]=V("external_shock_duration");       				//defines how long the shock lasts
		v[11]=V("external_shock_size");           				//defines the size, in percentage, of the shock
		if(t>=v[9]&&t<v[9]+v[10])
			v[12]=v[8]*(1+v[11]);
		else
			v[12]=v[8];

		v[13]=v[12]*v[0];
	//	}
	//else														//if it is not annual period
	//	v[13]=v[0];												//use last period income
RESULT(max(0,v[13]))


EQUATION("Capital_Flows")
	v[0]=V("External_Income");
	v[1]=V("Basic_Interest_Rate");
	v[2]=V("external_interest_rate");
	v[3]=V("capital_flow_adjustment");
	v[4]=(v[1]-v[2])*v[0]*v[3];
RESULT(v[4])



EQUATION("Trade_Balance")
/*
The trade balance is obtained by the difference between total exports and total imports.
*/
	v[0]=V("Country_Nominal_Exports");
	v[1]=V("Country_Nominal_Imports");
	v[2]=V("Capital_Flows");
	v[3]=v[0]-v[1]+v[2];
RESULT(v[3])


EQUATION("International_Reserves")
RESULT(CURRENT+V("Trade_Balance"))


EQUATION("Exchange_Rate")
/*
Nominal exchange rate.
*/
	v[0]=CURRENT;
	v[1]=VL("Trade_Balance",1);
	v[2]=V("exchange_rate_adjustment");
	if(v[1]<0)
		v[3]=v[0]+v[2];
	else if(v[1]>0)
		v[3]=v[0]-v[2];
	else
		v[3]=v[0];
	
RESULT(max(0.01,v[3]))
