/*****EXTERNAL SECTOR*****/


EQUATION("External_Income")
/*
Nominal value of external income.
*/
	v[0]=CURRENT;
	v[1]=V("annual_frequency");
	v[2]=fmod((double) t,v[1]);                					//divides the time period by annual adjustment period (adjust annualy)
	if(v[2]==0)                               					//if the rest of the division is zero (adjust external income)
		{
		v[3]=V("external_income_growth");						//fixed external income growth
		v[4]=V("external_income_sd");							//fixed external income sd
		v[5]=LAG_GROWTH(country, "Country_GDP", v[1], 1);
		v[7]=V("external_income_adjustmnent");                  //exogenous parameter that amplifies external growth based on domestic growth
		v[8]=1+norm((v[3]+v[5]*v[7]), v[4]);					//random draw from a normal distribution with average equals to past growth and standard deviation equals to past growth in absolute value
		
		v[9]=V("external_shock_begin");          				//defines when the shock happens
		v[10]=V("external_shock_duration");       				//defines how long the shock lasts
		v[11]=V("external_shock_size");           				//defines the size, in percentage, of the shock
		if(t>=v[9]&&t<v[9]+v[10])
			v[12]=v[8]*(1+v[11]);
		else
			v[12]=v[8];

		v[13]=v[12]*v[0];
		}
	else														//if it is not annual period
		v[13]=v[0];												//use last period income
RESULT(max(0,v[13]))


EQUATION("Country_Capital_Flows")
	v[0]=V("External_Income");
	v[1]=V("Central_Bank_Basic_Interest_Rate");
	v[2]=V("external_interest_rate");
	v[5]=pow(1+v[2],1/V("annual_frequency"))-1;
	v[3]=V("external_capital_flow_adjustment");
	v[4]=(v[1]-v[5])*v[0]*v[3];
RESULT(v[4])


EQUATION("Country_Trade_Balance")
RESULT(V("Country_Nominal_Exports")-V("Country_Nominal_Imports"))


EQUATION("Country_International_Reserves")
RESULT(CURRENT+V("Country_Trade_Balance")+V("Country_Capital_Flows");)


EQUATION("Country_International_Reserves_GDP_Ratio")
	v[0]=V("annual_frequency");
	v[1]=V("Country_International_Reserves");
	v[2]=LAG_SUM(country, "Country_GDP", v[0]);
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])


EQUATION("Country_Exchange_Rate")
/*
Nominal exchange rate.
*/
	v[0]=CURRENT;
	v[1]=VL("Country_Trade_Balance",1)+VL("Country_Capital_Flows",1);
	v[2]=V("exchange_rate_adjustment");
	if(v[1]<0)
		v[3]=v[0]+v[2];
	else if(v[1]>0)
		v[3]=v[0]-v[2];
	else
		v[3]=v[0];
	
RESULT(max(0.01,v[3]))


EQUATION("Basic_Interest_Rate_Min")
v[0]=V("external_interest_rate");
v[1]=VS(centralbank, "cb_target_international_reserves");
v[2]=VL("Country_GDP",1);
v[3]=VL("Country_GDP",2);
v[4]=VL("Country_GDP",3);
v[5]=VS(government, "government_expectations");
v[6]=VL("Country_International_Reserves",1);
v[7]=VL("Country_Nominal_Exports",1);
v[8]=VL("Country_Nominal_Imports",1);
v[9]=VL("External_Income",1);
v[10]=VL("External_Income",2);

v[11]= v[3]!=0? v[5]*(v[2]-v[3])/v[3] : 0;//domestic expected growth
v[12]= v[10]!=0? v[5]*(v[9]-v[10])/v[10] : 0;//external exprected growth

v[13]=V("external_capital_flow_adjustment");

v[14]=v[2]*(2+v[11])+v[3]+v[4];//expected annual gdp
v[15]=v[13]*v[9]*(1+v[12]);

v[16]= v[15]!=0? v[0] + (v[1]*v[14] - v[6] - v[7]*(1+v[12]) + v[8]*(1+v[11]))/v[15] : 0;
RESULT(max(0,v[16]))












