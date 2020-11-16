
/**********************************************************************
Bank Credit Demand and Supply
*********************************************************************/


EQUATION("Bank_Max_Total_Loans");
/*
Maximum new loans. Follows basileia or similar rule
Might impact effective loans
*/
	
	v[0]=VL("Bank_Accumulated_Profits",1);
	v[1]=V("minimum_capital_ratio");
	v[2]=V("fragility_sensitivity");
	v[3]=VL("Avg_Debt_Rate_Firms",1);
	v[4]=VL("Bank_Default_Share",1);
	v[5]=V("default_sensitivity");	
	if(v[1]!=0)
		v[6]=v[0]/(v[1]*(1+v[2]*v[3]+v[5]*v[4]));
	else
		v[6]=-1;
	v[8]=max(0,v[6]);
RESULT(v[8])


EQUATION("Bank_Demand_Loans")
/*
Total demand for loans, firms and classes
*/
	v[10]=V("id_bank");

	v[0]=0;
	CYCLES(root, cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[2]=VS(cur1, "Firm_Demand_Loans");
			v[3]=VS(cur1, "id_firm_bank");
			if(v[3]==v[10])
				v[1]=v[1]+v[2];
			else
				v[1]=v[1];
		}
		v[0]=v[0]+v[1];
	}
	
	v[4]=0;
	CYCLES(root, cur, "CLASSES")
	{
		v[5]=VS(cur, "Class_Demand_Loans");
		v[4]=v[4]+v[5];
	}
	v[6]=V("Bank_Market_Share");
	v[7]=v[0]+v[6]*v[4];
	
RESULT(v[7])


EQUATION("Bank_Effective_Loans")
/*
Effective Loans is the minimum between demanded loans and max loans.
*/
	v[0]=V("Bank_Demand_Loans");
	v[1]=V("Bank_Max_Total_Loans");
	v[2]=V("depreciation_period");
	v[3]=VL("Bank_Total_Stock_Loans",1);
	v[4]=max(0,(v[1]-v[3]));
	v[5]=V("id_public_bank");
	v[6]=V("begin_credit_rationing");
	if(t>v[6]&&v[6]!=-1&&v[5]!=1&&v[1]!=-1)
		v[7]=min(v[0],v[4]);
	else//no credit rationing, all demand met
		v[7]=v[0];
RESULT(max(0,v[7]))


EQUATION("Bank_Demand_Met")
/*
Share of demand for new loans met
*/
	v[0]=V("Bank_Effective_Loans");
	v[1]=V("Bank_Demand_Loans");
	if(v[1]!=0)
		v[2]=v[0]/v[1];
	else
		v[2]=1;
RESULT(v[2])


/**********************************************************************
Bank Competition
*********************************************************************/

EQUATION_DUMMY("Bank_Number_Clients", "Loans_Distribution_Firms")


EQUATION("Bank_Competitiveness")
/*
Bank competitiveness depends negativelly on the bank interest rate on loans and the loans not met
*/
	v[0]=VL("Bank_Competitiveness",1);                                 //bank's competitiveness in the last period
	v[1]=VL("Bank_Default_Share",1);                                   //bank share of defaulted loans
	v[2]=VL("Bank_Demand_Met",1);                                      //bank demand not met
	v[3]=VL("Bank_Interest_Rate_Long_Term",1);                  	   //bank interest rate on loans in the last period
	v[4]=VL("Bank_Interest_Rate_Short_Term",1);                  	   //bank interest rate on short term loans in the last period
	
	v[5]=V("e_default");
	v[6]=V("e_rationing");  
	v[7]=V("e_interest_long_term");	
	v[8]=V("e_interest_short_term");	
   	if(v[2]!=0&&v[3]!=0&&v[4]!=0)                                      							//if competitiveness' determinants are not zero
     	v[9]=(pow((1-v[1]),v[5]))*(pow(v[2],v[6]))*(1/pow(v[3],v[7]))*(1/pow(v[4],v[8])); 
   	else                                                               							//if either the interest rate or the loans not met was zero 
     	v[9]=v[0];                                                     							//bank's competitiveness will be the competitiveness in the last period
RESULT(v[9])


EQUATION("Bank_Market_Share")
/*
Bank Market Share evolves based on the bank competitiveness and sector average competitiveness
*/
	v[0]=VL("Bank_Market_Share", 1);                //bank's market share in the last period
	v[1]=V("Avg_Competitiveness_Financial_Sector"); //sector average competitiveness
	v[3]=V("Bank_Competitiveness");                 //bank's competitiveness
	if(v[1]!=0)                                     //if the sector average competitiveness is not zero
		v[4]=v[0]+v[0]*((v[3]/v[1])-1);             //bank's market share will be the last period's inscresed by the adjustment paramter times the ratio between firm's competitiveness and sector average competitiveness
	else                                            //if the sector average competitiveness is zero
		v[4]=0;                                     //bank's market share will be zero 
RESULT(v[4])


EQUATION("Bank_Desired_Long_Term_Spread")
/*
Bank Variable
*/
	v[0]=VL("Bank_Desired_Long_Term_Spread",1);                            //bank desired spread in the last period 
  	v[1]=VL("Bank_Competitiveness",1);                                     //bank's competitiveness in the last period
  	v[2]=VL("Avg_Competitiveness_Financial_Sector",1);                     //sector's average competitiveness in the last period
  	if (v[2]!=0)
  		v[3]=(v[1]-v[2])/v[2];                                             //diference between bank's competitiveness and sector's average competitiveness 
  	else
  		v[3]=0;
  	v[4]=v[0]*(1+v[3]);	
  	
  	v[5]=VL("Bank_Expected_Profit_Rate",1);
  	v[6]=V("target_profit_rate");
  	v[7]=V("long_term_spread_adjustment");
  	if(v[5]<v[6])
  		v[8]=v[0]+v[7];
  	else
  		v[8]=v[0];
  	
  	
  	
  	      
  	
  	v[10]=VL("Bank_Short_Term_Rate",1);
	v[11]=VL("Bank_Interest_Rate_Short_Term",1);
	v[12]=VL("Bank_Interest_Rate_Long_Term",1);
	v[13]=VL("Interest_Rate_Deposits",1);
	v[14]=VL("Bank_Leverage",1);
	v[15]=V("financial_sector_profits_distribution_rate");
	v[16]=VL("Bank_Default_Share",1);
	v[17]=V("risk_premium_adjustment");
	v[18]=VL("Avg_Debt_Rate_Firms",1);
	v[19]=VL("Avg_Debt_Rate_Class",1);
	if(v[14]!=0)
		v[20]=v[10]*v[11]*(1+v[17]*v[19])+(1-v[10])*v[12]*(1+v[17]*v[18])-(v[13]/v[14])-v[16];
	else
		v[20]=0;
  	
  	                                                            					
RESULT(max(0,v[8])) 


EQUATION("Bank_Desired_Interest_Rate_Long_Term")
/*
Bank desired interest rate on loans is the current base interest rate with a bank desired spread
*/
	v[0]=V("Bank_Desired_Long_Term_Spread");                         //bank's desired spread
	v[1]=V("Basic_Interest_Rate");                          		 //central bank interest rate
	v[2]=(1+v[0])*v[1];                                  	         //bank's desired interest rate
RESULT(v[2])


EQUATION("Bank_Interest_Rate_Long_Term")
/*
Bank's effective interest rate on loans is a average between the desired interest rate and the sector average interest rate
*/
	v[0]=VL("Bank_Interest_Rate_Long_Term",1);                                 //bank's interest rate on loans in the last period
	v[1]=V("Bank_Desired_Interest_Rate_Long_Term");                            //bank's desired interest rate on loans
	v[2]=V("price_strategy_long_term");                                        //weight parameter for long term interest rates
	v[3]=VL("Avg_Interest_Rate_Long_Term", 1);                                 //sector average interest rate on loans in the last period
	if(v[2]==0)
		v[4]=(1+V("long_term_loans_spread"))*V("Basic_Interest_Rate");
	else	
		v[4]=v[2]*(v[1])+(1-v[2])*(v[3]);                                      //firm's price is a average between the desired price and the sector average price
	
	v[10]=V("minimum_long_term_interest_rate");
	if(v[1]>0)                                                                 //if desired interest rate is positive
		v[5]=max(v[10],v[4]);                                                  //bank's interest rate can never be less than a minimum, even if the basic rate is zero
	else                                                                       //if desired interest rate is not positive
		v[5]=v[0];                                                             //bank's interest rate will be the last period's
	
	v[6]=V("id_public_bank");
	if(v[6]==1)
	{
		v[7]=V("public_long_term_spread");                               //public bank long term spread 
		v[8]=V("Basic_Interest_Rate");                          		 //central bank interest rate
		v[9]=(1+v[7])*v[8];                                  	         //publiuc bank's interest rate
	}
	else
		v[9]=v[5];
RESULT(v[9])


EQUATION("Bank_Desired_Short_Term_Spread")
/*
Bank Variable
*/
	v[0]=VL("Bank_Desired_Short_Term_Spread",1);                           //bank desired spread in the last period 
  	v[1]=VL("Bank_Competitiveness",1);                                     //bank's competitiveness in the last period
  	v[2]=VL("Avg_Competitiveness_Financial_Sector",1);                     //sector's average competitiveness in the last period
  	if (v[2]!=0)
  		v[3]=(v[1]-v[2])/v[2];                                             //diference between bank's competitiveness and sector's average competitiveness 
  	else
  		v[3]=0;
  	v[4]=v[0]*(1+v[3]);	  
  	
  	
  	v[5]=VL("Bank_Expected_Profit_Rate",1);
  	v[6]=V("target_profit_rate");
  	v[7]=V("short_term_spread_adjustment");
  	if(v[5]<v[6])
  		v[8]=v[0]+v[7];
  	else
  		v[8]=v[0];
  		
  		                                                                					
RESULT(max(0,v[8])) 


EQUATION("Bank_Desired_Interest_Rate_Short_Term")
/*
Bank desired interest rate on loans is the current base interest rate with a bank desired spread
*/
	v[0]=V("Bank_Desired_Short_Term_Spread");                        //bank's desired spread
	v[1]=V("Basic_Interest_Rate");                          		 //central bank interest rate
	v[2]=(1+v[0])*v[1];                                  	         //bank's desired interest rate
RESULT(v[2])


EQUATION("Bank_Interest_Rate_Short_Term")
/*
Bank's effective interest rate on loans is a average between the desired interest rate and the sector average interest rate
*/
	v[0]=VL("Bank_Interest_Rate_Short_Term",1);                                //bank's interest rate on loans in the last period
	v[1]=V("Bank_Desired_Interest_Rate_Short_Term");                           //bank's desired interest rate on loans
	v[2]=V("price_strategy_short_term");                                       //weight parameter for short tem interest rates
	v[3]=VL("Avg_Interest_Rate_Short_Term", 1);                                //sector average interest rate on loans in the last period
	if(v[2]==0)
		v[4]=(1+V("short_term_loans_spread"))*V("Basic_Interest_Rate");
	else	
		v[4]=v[2]*(v[1])+(1-v[2])*(v[3]);                                          //firm's price is a average between the desired price and the sector average price
	
	v[10]=V("minimum_short_term_interest_rate");
	if(v[1]>0)                                                                 //if desired interest rate is positive
		v[5]=max(v[10],v[4]);                                                  //bank's interest rate can never be less than a minimum, even if the basic rate is zero
	else                                                                       //if desired interest rate is not positive
		v[5]=v[0];                                                             //bank's interest rate will be the last period's
	
	v[6]=V("id_public_bank");
	if(v[6]==1)
	{
		v[7]=V("public_short_term_spread");                               //public bank short term spread 
		v[8]=V("Basic_Interest_Rate");                          		 //central bank interest rate
		v[9]=(1+v[7])*v[8];                                  	         //publiuc bank's interest rate
	}
	else
		v[9]=v[5];
RESULT(v[9])


/**********************************************************************
Bank Stocks and Flows - Collection from bank's clients
*********************************************************************/


EQUATION("Bank_Stock_Deposits")
/*
Total Stock of deposits, firms and classes
*/
	
	v[0]=V("id_bank");
	v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=0; 					//initializes temporary storages for macro sum
	CYCLES(root, cur, "SECTORS")						//cycle trough sectors
	{
		v[7]=v[8]=v[9]=v[10]=v[11]=v[12]=0;				//initialalizes temporaty storages for sectoral sums
		CYCLES(cur, cur1, "FIRMS")					//cycle trough firms
		{
			v[13]=VS(cur1, "id_firm_bank");				//firm bank identifies
			if(v[13]==v[0])						//if the firm is client of this bank
				{
				v[7]+=VS(cur1, "Firm_Stock_Deposits");
				v[8]+=VS(cur1, "Firm_Stock_Loans_Short_Term");
				v[9]+=VS(cur1, "Firm_Stock_Loans_Long_Term");
				v[10]+=VS(cur1, "Firm_Deposits_Return");
				v[11]+=VS(cur1, "Firm_Interest_Payment");
				v[12]+=VS(cur1, "Firm_Debt_Payment");
				}
		}
		v[1]+=v[7];
		v[2]+=v[8];
		v[3]+=v[9];
		v[4]+=v[10];
		v[5]+=v[11];
		v[6]+=v[12];
	}
	
	v[14]=V("Bank_Market_Share");
	CYCLES(root, cur, "CLASSES")
	{
		v[1]+=v[14]*(VS(cur, "Class_Stock_Deposits"));
		v[2]+=v[14]*(VS(cur, "Class_Stock_Loans"));
		v[4]+=v[14]*(VS(cur, "Class_Deposits_Return"));
		v[5]+=v[14]*(VS(cur, "Class_Interest_Payment"));
		v[6]+=v[14]*(VS(cur, "Class_Debt_Payment"));
	}
	
WRITE("Bank_Stock_Loans_Short_Term", v[2]);
WRITE("Bank_Stock_Loans_Long_Term", v[3]);
WRITE("Bank_Total_Stock_Loans", v[2]+v[3]);
WRITE("Bank_Interest_Payment", v[4]);
WRITE("Bank_Interest_Receivment", v[5]);
WRITE("Bank_Debt_Payment", v[6]);

RESULT(v[1])


EQUATION_DUMMY("Bank_Stock_Loans_Short_Term", "Bank_Stock_Deposits")
EQUATION_DUMMY("Bank_Stock_Loans_Long_Term", "Bank_Stock_Deposits")
EQUATION_DUMMY("Bank_Total_Stock_Loans", "Bank_Stock_Deposits")
EQUATION_DUMMY("Bank_Interest_Payment", "Bank_Stock_Deposits")
EQUATION_DUMMY("Bank_Interest_Receivment", "Bank_Stock_Deposits")
EQUATION_DUMMY("Bank_Debt_Payment", "Bank_Stock_Deposits")


/**********************************************************************
Bank Profits
*********************************************************************/


EQUATION("Bank_Defaulted_Loans");
/*
Current bank defaulted loans 
*/
v[0]=V("bank_defaulted_loans_temporary");
WRITE("bank_defaulted_loans_temporary", 0);
RESULT(v[0])


EQUATION("Bank_Accumulated_Defaulted_Loans");
/*
Current bank defaulted loans 
*/
v[0]=VL("Bank_Accumulated_Defaulted_Loans",1);
v[1]=V("Bank_Defaulted_Loans");
v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Bank_Profits")
/*
Current bank profits is the difference between Interest Return and Interest Payment, minus defaulted loans. can be negative
*/
v[0]=V("Bank_Interest_Receivment");
v[1]=V("Bank_Interest_Payment");
v[2]=V("Bank_Defaulted_Loans");
v[3]=v[0]-v[1]-v[2];
RESULT(v[3])


EQUATION("Bank_Distributed_Profits")
/*
Current bank profits distributed 
*/
v[0]=V("Bank_Profits");
v[1]=V("bank_profit_distribution");
if(v[0]>0)
	v[2]=v[0]*v[1];
else
	v[2]=0;
RESULT(v[2])


EQUATION("Bank_Retained_Profits")
/*
Current bank profits retained
*/
v[0]=V("Bank_Profits");
v[1]=V("Bank_Distributed_Profits");
v[2]=v[0]-v[1];
/*
v[1]=V("Bank_Total_Stock_Loans");
v[2]=V("minimum_capital_ratio");
v[3]=V("fragility_sensitivity");
v[4]=VL("Avg_Debt_Rate_Firms",1);
v[5]=v[3]*v[4];
v[6]=VL("Bank_Default_Share",1);
v[7]=V("default_sensitivity");
v[8]=v[7]*v[6];	
v[9]=(v[2]*(1+v[5]+v[8]))*v[1];           //needed net worth for current stock os loans
//v[9]=v[2]*v[1];           //needed net worth for current stock os loans

v[10]=VL("Bank_Accumulated_Profits",1);    //current net worth
v[11]=v[9]-v[10];						   //needed retained profits
v[12]=max(0,v[11]);
v[13]=min(v[0],v[12]);
*/
RESULT(v[2])


EQUATION("Bank_Accumulated_Profits")
/*
Total Stock of deposits of the financial sector
*/
v[0]=VL("Bank_Accumulated_Profits",1);
v[3]=V("Bank_Retained_Profits");
v[4]=v[3]+v[0];

if(v[4]<0)
{
	v[5]=V("minimum_capital_ratio");
	v[13]=VL("Bank_Total_Stock_Loans",1);
	v[14]=v[13]*v[5];							//minimal capital required to current stock of loans
	v[15]=-v[4]+v[14];							//central bank loans (rescue)
	WRITE("Bank_Rescue", v[15]);	
}
else
{
	v[14]=v[4];
	v[15]=0;
	WRITE("Bank_Rescue", v[15]);
}
RESULT(v[14])

EQUATION_DUMMY("Bank_Rescue", "Bank_Accumulated_Profits")


/**********************************************************************
Bank Analysis
*********************************************************************/


EQUATION("Bank_Short_Term_Rate");
/*
Share of short term loans over total loans
*/
	v[0]=V("Bank_Stock_Loans_Short_Term");
	v[1]=V("Bank_Total_Stock_Loans");
	if(v[1]!=0)
		v[2]=v[0]/v[1];
	else
		v[2]=0;
RESULT(v[2])


EQUATION("Bank_Leverage")
/*
Total Stock of loans over total stock of deposits
*/
v[0]=V("Bank_Total_Stock_Loans");
v[1]=V("Bank_Stock_Deposits");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])


EQUATION("Bank_Default_Share");
/*
Current bank defaulted loans over stock of long term loans
*/
v[0]=V("Bank_Defaulted_Loans");
v[1]=V("Bank_Total_Stock_Loans");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(min(1,v[2]))


EQUATION("Bank_Effective_Capital_Ratio");
/*
Current bank accumulated profits over stock of loans
*/
v[0]=V("Bank_Accumulated_Profits");
v[1]=V("Bank_Total_Stock_Loans");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(min(1,v[2]))


EQUATION("Bank_Expected_Profit_Rate");
/*
Expected profit rate on total loans, based on last period
*/
	v[0]=VL("Bank_Short_Term_Rate",1);
	v[1]=VL("Bank_Interest_Rate_Short_Term",1);
	v[2]=VL("Bank_Interest_Rate_Long_Term",1);
	v[3]=VL("Interest_Rate_Deposits",1);
	v[4]=VL("Bank_Leverage",1);
	v[5]=V("financial_sector_profits_distribution_rate");
	v[6]=VL("Bank_Default_Share",1);
	v[7]=V("risk_premium_adjustment");
	v[8]=VL("Avg_Debt_Rate_Firms",1);
	v[9]=VL("Avg_Debt_Rate_Class",1);
	if(v[4]!=0)
		v[10]=v[0]*v[1]*(1+v[7]*v[9])+(1-v[0])*v[2]*(1+v[7]*v[8])-(v[3]/v[4])-v[6];
	else
		v[10]=0;
RESULT(v[10])
	

EQUATION("Bank_Effective_Profit_Rate_1");
/*
Effective profit rate on total loans
*/
	v[0]=V("Bank_Short_Term_Rate");
	v[1]=V("Bank_Interest_Rate_Short_Term");
	v[2]=V("Bank_Interest_Rate_Long_Term");
	v[3]=V("Interest_Rate_Deposits");
	v[4]=V("Bank_Leverage");
	v[5]=V("financial_sector_profits_distribution_rate");
	v[6]=V("Bank_Default_Share");
	v[7]=V("risk_premium_adjustment");
	v[8]=V("Avg_Debt_Rate_Firms");
	v[9]=V("Avg_Debt_Rate_Class");
	if(v[4]!=0)
		v[10]=v[0]*v[1]*(1+v[7]*v[9])+(1-v[0])*v[2]*(1+v[7]*v[8])-(v[3]/v[4])-v[6];
	else
		v[10]=0;
RESULT(v[10])


EQUATION("Bank_Effective_Profit_Rate_2");
/*
Effective profit rate on total loans
*/
	v[0]=V("Bank_Profits");
	v[1]=V("Bank_Total_Stock_Loans");
	if(v[1]!=0)
		v[2]=v[0]/v[1];
	else
		v[2]=0;
RESULT(v[2])



