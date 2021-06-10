

/*******************************************************************************
Interest Rates
*******************************************************************************/

EQUATION("CB_Inflation_Gap")

	v[1]=V("cb_target_annual_inflation");
	v[0]=VL("Country_Consumer_Price_Index",1);
	v[2]=VS(government,"government_expectations");
	v[3]=LAG_GROWTH(country, "Country_Consumer_Price_Index", 1, 1);
	v[4]=v[0]*(1+v[2]*v[3]);
	v[5]=VL("Country_Consumer_Price_Index",V("annual_frequency"));
	v[6]= v[5]!=0? (v[4]-v[5])/v[5] : 0;
	v[7]=(v[6]-v[1])/v[1];
RESULT(v[7])


EQUATION("CB_Output_Gap")
	v[0]=VL("Country_Real_GDP",1);
	v[1]=VS(government,"government_expectations");
	v[2]=VL("Country_Annual_Real_Growth",1);
	v[3]=V("annual_frequency");
	v[4]=LAG_AVE(p,"Country_Real_GDP",v[3],2);
	v[5]=v[4]*(1+v[1]*v[2]/v[3]);
	v[6]= v[5]!=0? (v[0]-v[5])/v[5] : 0;
RESULT(v[6])


EQUATION("Central_Bank_Basic_Interest_Rate")
/*
Nominal Interest rate is set by the central bank following a (possible) dual mandate Taylor Rule, considering the inflation and unemployment gaps.
"switch_monetary_policy":
0-->       no monetary policy rule
1-->       taylor rule
2-->       smithin rule
3--> 	   pasinetti rule
4-->       kansas city rule


*/
	
	v[0]=V("cb_quarterly_nominal_interest_rate");
	
	v[1]=V("cb_target_annual_inflation");
	v[2]=V("cb_target_capacity");
	v[3]=V("cb_target_credit_growth");
	v[4]=V("cb_target_debt_rate");
	v[5]=VS(external,"exchange_rate_max");
	v[6]=VS(external,"exchange_rate_min");
	
	v[11]=VL("Country_Annual_CPI_Inflation",1);
	v[12]=VL("Country_Idle_Capacity",1);
	v[13]=VL("Financial_Sector_Total_Stock_Loans_Growth",1);
	v[14]=VL("Country_Debt_Rate_Firms",1);
	v[15]=VL("Country_Exchange_Rate",1);
	v[16]=LAG_GROWTH(country, "Country_Avg_Productivity", 1,1);
	
	v[60]=VL("Country_Consumer_Price_Index",1);
	v[61]=VS(government,"government_expectations");
	v[47]=LAG_GROWTH(country, "Country_Consumer_Price_Index", 1, 1);
	v[62]=v[60]*(1+v[61]*v[47]);
	v[63]=VL("Country_Consumer_Price_Index",V("annual_frequency"));
	v[64]= v[63]!=0? (v[62]-v[63])/v[63] : 0;
	
	if(V("switch_foroward_looking")==1)
		v[21]=(v[64]-v[1])/v[1];
	else
		v[21]=(v[11]-v[1])/v[1];
	v[22]=(v[12]-v[2])/v[2];
	v[23]=max(0,(v[13]-v[3])/v[3]);
	v[24]=max(0,(v[14]-v[4])/v[4]);
	v[25]=max(0,(v[15]-v[5])/v[5]);
	v[26]=min(0,(v[15]-v[6])/v[6]);
	
	
	v[30]=V("switch_monetary_policy");
	
	if(v[30]==0)//no monetary policy rule, fixed nominal interest rate set by "cb_quarterly_nominal_interest_rate" parameter
		v[40]=v[0];
	
	if(v[30]==1)//taylor rule
	{
		v[31]=V("cb_sensitivity_inflation");
		v[32]=V("cb_sensitivity_capacity");
		v[33]=V("cb_sensitivity_credit_growth");
		v[34]=V("cb_sensitivity_debt_rate");
		v[35]=V("cb_sensitivity_exchange");

		v[40]=v[0]*(1
			 +v[31]*v[21]
			 -v[32]*v[22]
			 +v[33]*v[23]
			 +v[34]*v[24]);
	}
	
	if(v[30]==2)//smithin rule
		v[40]=v[47];
	
	if(v[30]==3)//pasinetti rule
		v[40]=v[47]+v[16];


	if(v[30]==4)//kansas city rule.
		v[40]=0;

	//Smoothing
	v[41]=V("cb_smoothing");
	v[42]=CURRENT;
	v[43]=v[40]*(1-v[41]) + v[41]*v[42];
	
	//Regime Begin
	v[44]=V("begin_monetary_policy");
	if(t>v[44]&&v[44]!=-1)
		v[45]=v[43];
	else
		v[45]=v[42];
	
	v[46]=max(0,v[45]);
	v[48]= v[46]-v[47];
	WRITE("CB_Quarterly_Real_Interest_Rate", v[48]);
	
	
	v[50]=VL("CB_Credibility",1);
	v[51]=abs((v[11]-v[1])/v[1]);
	v[52]=V("cb_credibility_tolerance");
	v[53]=V("cb_credibility_adjustment");
	if(v[51]>v[52])
		v[54]=v[50]-v[53];
	else
		v[54]=v[50]+v[53];
	v[55]=max(0.00,min(1,v[54]));
	WRITE("CB_Credibility", v[55]);
	
	v[60]=VL("Country_Consumer_Price_Index",1);
	v[61]=VS(government,"government_expectations");
	v[62]=v[60]*(1+v[61]*v[47]);
	v[63]=VL("Country_Consumer_Price_Index",V("annual_frequency"));
	v[64]= v[63]!=0? (v[62]-v[63])/v[63] : 0;
	
	v[71]=V("cb_interest_rate_min");
	v[72]=V("cb_interest_rate_max");
	v[73]=max(min(v[45],v[72]),v[71]);	
	
	v[80]=V("interest_shock_begin");          				//defines when the shock happens
	v[81]=V("interest_shock_duration");       				//defines how long the shock lasts
	v[82]=V("interest_shock_size");           				//defines the size, in percentage, of the shock
	if(t>=v[80]&&t<v[80]+v[81]&&v[81]!=0)
		v[83]=v[82];
	else
		v[83]=v[73];
	
RESULT(v[83])

EQUATION_DUMMY("CB_Credibility", "Central_Bank_Basic_Interest_Rate")
EQUATION_DUMMY("CB_Quarterly_Real_Interest_Rate", "Central_Bank_Basic_Interest_Rate")


EQUATION("Financial_Sector_Interest_Rate_Deposits")
/*
Interest Rate on Bank deposits is a negative spreaded base interest rate
*/
v[0]=V("Central_Bank_Basic_Interest_Rate");
v[1]=V("fs_spread_deposits");
v[2]=max(0,(v[0]-v[1]));
RESULT(v[2])


/*******************************************************************************
Financial Sector Aggregates and Averages
*******************************************************************************/

EQUATION("Financial_Sector_Avg_Competitiveness")
/*
Average competitiveness, weighted by firm's market share
*/
	v[0]=0;                                           //initializes the CYCLE
	CYCLE(cur, "BANKS")                               //CYCLE trought all banks in the sector
	{
		v[1]=VS(cur, "Bank_Competitiveness");         //bank's competitiveness
		v[2]=VLS(cur, "Bank_Market_Share", 1);        //bank's market share in the last period
		v[0]=v[0]+v[1]*v[2];                          //sector average competitiveness will be a average of bank competitiveness weighted by their respective market shares
	}
RESULT(v[0])

EQUATION("Financial_Sector_Avg_Interest_Rate_Long_Term")
RESULT(WHTAVE("Bank_Interest_Rate_Long_Term", "Bank_Market_Share"))

EQUATION("Financial_Sector_Avg_Interest_Rate_Short_Term")
RESULT(WHTAVE("Bank_Interest_Rate_Short_Term", "Bank_Market_Share"))

EQUATION("Financial_Sector_Stock_Loans_Short_Term")
RESULT(SUM("Bank_Stock_Loans_Short_Term"))

EQUATION("Financial_Sector_Stock_Loans_Long_Term")
RESULT(SUM("Bank_Stock_Loans_Long_Term"))

EQUATION("Financial_Sector_Total_Stock_Loans")
RESULT(SUM("Bank_Total_Stock_Loans"))

EQUATION("Financial_Sector_Defaulted_Loans")
RESULT(SUM("Bank_Defaulted_Loans"))

EQUATION("Financial_Sector_Stock_Deposits")
RESULT(SUM("Bank_Stock_Deposits"))

EQUATION("Financial_Sector_Max_Total_Loans");
RESULT(SUM("Bank_Max_Total_Loans"))

EQUATION("Financial_Sector_Demand_Loans")
RESULT(SUM("Bank_Demand_Loans"))

EQUATION("Financial_Sector_Effective_Loans")
RESULT(SUM("Bank_Effective_Loans"))

EQUATION("Financial_Sector_Interest_Payment")
RESULT(SUM("Bank_Interest_Payment"))

EQUATION("Financial_Sector_Interest_Receivment")
RESULT(SUM("Bank_Interest_Receivment"))

EQUATION("Financial_Sector_Debt_Payment")
RESULT(SUM("Bank_Debt_Payment"))

EQUATION("Financial_Sector_Profits")
RESULT(SUM("Bank_Profits"))

EQUATION("Financial_Sector_Distributed_Profits")
RESULT(SUM("Bank_Distributed_Profits"))

EQUATION("Financial_Sector_Accumulated_Profits")
RESULT(SUM("Bank_Accumulated_Profits"))

EQUATION("Financial_Sector_Rescue")
RESULT(SUM("Bank_Rescue"))

EQUATION("Financial_Sector_Accumulated_Rescue")
RESULT(CURRENT + V("Financial_Sector_Rescue"))

EQUATION("Financial_Sector_Accumulated_Defaulted_Loans")
RESULT(CURRENT + V("Financial_Sector_Defaulted_Loans"))


/*******************************************************************************
Financial Sector Analysis
*******************************************************************************/


EQUATION("Financial_Sector_Short_Term_Rate");
/*
Share of short term loans over total loans
Analysis Variable
*/
	v[0]=V("Financial_Sector_Stock_Loans_Short_Term");
	v[1]=V("Financial_Sector_Total_Stock_Loans");
	v[2]= v[1]!=0? v[0]/v[1] : 0;
RESULT(v[2])


EQUATION("Financial_Sector_Default_Rate")
/*
Total Defaluted Loans over total stock of loans
Analysis Variable
*/
	v[0]=V("Financial_Sector_Defaulted_Loans");
	v[1]=V("Financial_Sector_Stock_Loans_Long_Term");
	v[2]= v[1]!=0? v[0]/v[1] : 0;
RESULT(v[2])


EQUATION("Financial_Sector_Demand_Met")
/*
Share of demand for new loans met
Analysis Variable
*/
	v[0]=V("Financial_Sector_Effective_Loans");
	v[1]=V("Financial_Sector_Demand_Loans");
	v[2]= v[1]!=0? v[0]/v[1] : 1;
RESULT(v[2])


EQUATION("Financial_Sector_Leverage")
/*
Total Stock of Loans over Total Stock of Deposits
Analysis Variable
*/
	v[0]=V("Financial_Sector_Total_Stock_Loans");
	v[1]=V("Financial_Sector_Stock_Deposits");
	v[2]= v[1]!=0? v[0]/v[1] : 0;
RESULT(v[2])


EQUATION("Financial_Sector_Effective_Capital_Ratio")
/*
Accumulated profits over total loans
Analysis Variable
*/
	v[0]=V("Financial_Sector_Accumulated_Profits");
	v[1]=V("Financial_Sector_Total_Stock_Loans");
	v[2]= v[1]!=0? v[0]/v[1] : 0;
RESULT(v[2])


EQUATION("Financial_Sector_Normalized_HHI")
/*
Financial Sector Variable for Analysis
*/
	v[0]=0;                           		//initializes the CYCLE    
	CYCLE(cur, "BANKS")               		//CYCLE trought all firms of the sector
	{
		v[1]=VS(cur, "Bank_Market_Share");  //firm's market share
		v[0]=v[0]+v[1]*v[1];            	//sums up firm's market share squared
	}
	v[2]=COUNT("BANKS");
	if (v[2]!=1)
		v[3]=(v[0]-(1/v[2]))/(1- (1/v[2]));
	else	
		v[3]=1;
RESULT(v[3])


EQUATION("Financial_Sector_Turbulence")
/*
Financial Sector Variable for Analysis
*/
	v[0]=0;                                           	 //initializes the CYCLE 
	CYCLE(cur, "BANKS")                              	 //CYCLE trough all firms 
	{
		v[2]=VS(cur,"Bank_Market_Share");   			 //firm's effective market share in current period
		v[3]=VLS(cur,"Bank_Market_Share",1);			 //firm's effective market share in the last period
		v[4]=abs(v[2]-v[3]);                             //returns the absolute value of the difference
		v[0]=v[0]+v[4];                                  //sums up all absolute values for all firms
	}
RESULT(v[0])


EQUATION("Financial_Sector_Total_Stock_Loans_Growth")
/*
Total credit growth
*/
	v[0]=V("Financial_Sector_Total_Stock_Loans");
	v[1]=VL("Financial_Sector_Total_Stock_Loans", 1);
	v[2]=v[1]!=0? (v[0]-v[1])/v[1] : 0;
RESULT(v[2])












