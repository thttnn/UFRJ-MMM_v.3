

/*******************************************************************************
Interest Rates
*******************************************************************************/

EQUATION("Central_Bank_Basic_Interest_Rate")
/*
Nominal Interest rate is set by the central bank following a (possible) dual mandate Taylor Rule, considering the inflation and unemployment gaps.
"switch_monetary_policy":
0-->       no monetary policy rule
1-->       single mandate (inflation) taylor rule
2-->       dual mandate (inflation and unemploymeny) taylor rule
3-->       triple mandate (inflation, unemployment and credit growth) taylor rule
4-->       triple mandate (inflation, unemployment and debt rate) taylor rule
5-->       smithin rule
6--> 	   pasinetti rule
7-->       kansas city rule

"cb_interest_rate_adjustment": absolute increase

*/
	
	v[0]=V("cb_annual_real_interest_rate");
	
	v[1]=V("cb_target_annual_inflation");
	v[2]=V("cb_target_capacity");
	v[3]=V("cb_target_credit_growth");
	v[4]=V("cb_target_debt_rate");
	v[10]=V("cb_target_reserves");
	
	v[5]=VL("Country_Annual_CPI_Inflation",1);
	v[6]=VL("Country_Idle_Capacity",1);
	v[7]=VL("Financial_Sector_Total_Stock_Loans_Growth",1);
	v[8]=VL("Country_Debt_Rate_Firms",1);
	v[9]=VL("Country_International_Reserves_GDP_Ratio",1);
	
	v[11]=LAG_GROWTH(country, "Country_Avg_Productivity", 1,1);
		
	v[18]=V("cb_interest_rate_adjustment");
	v[19]=pow(1+CURRENT,V("annual_frequency"))-1;					//annual basic interest
	
	v[12]=V("switch_monetary_policy");
	
	if(v[12]==0)      											//no monetary policy rule, fixed nominal interest rate set by "cb_annual_real_interest_rate" parameter
		v[20]=v[0]+v[1];
	
	if(v[12]==1)												//taylor rule
	{
		v[13]=V("cb_sensitivity_inflation");
		v[14]=V("cb_sensitivity_capacity");
		v[15]=V("cb_sensitivity_credit_growth");
		v[16]=V("cb_sensitivity_debt_rate");
		v[21]=V("cb_sensitivity_reserves");

		v[17]=v[0]+v[5]
			 +v[13]*(v[5]-v[1])
			 -v[14]*(v[6]-v[2])
			 +v[15]*max(0,v[7]-v[3])
			 +v[16]*max(0,v[8]-v[4])
			 -v[21]*min(0,v[9]-v[10]);
		
		if(abs(v[17]-v[19])>v[18]&&v[18]!=-1)
		{
			if(v[17]>v[19])
				v[20]=v[19]+v[18];
			else if(v[17]<v[19])
				v[20]=v[19]-v[18];
			else
				v[20]=v[19];
		}
		else
			v[20]=v[17];

	}
	
	if(v[12]==2)		//smithin rule
	v[20]=v[5];	
	
	if(v[12]==3)		//pasinetti rule
	v[20]=v[5]+v[11];

	if(v[12]==4)		//kansas city rule.
	v[20]=0;

		
	v[24]=V("begin_monetary_policy");
	if(t>v[24]&&v[24]!=-1)
		v[25]=v[20];
	else
		v[25]=v[19];
	
	v[29]=pow(1+v[25],1/V("annual_frequency"))-1;
	
RESULT(max(0,v[29]))


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
	v[0]=V("Financial_Sector_Accumulated_Defaulted_Loans");
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












