

EQUATION("Firm_Price_Period")
/*
This variable writes for each firm, if it is price adjustment period or not, assuming 1 or 0.
*/
	v[0]=V("sector_price_frequency");						//sector price period parameter
	v[1]=fmod((t+v[0]),v[0]);								//devides the current time step by the price period and takes the rest
	v[2]=V("id_firm_number");								//firm number
	v[3]=fmod((v[2]+v[0]),v[0]);							//divides the firm number by the price period and takes the rest
	if (v[3]==v[1])											//if the firm number rest matches the time step rest
		v[4]=1;												//mark as price period for the firm	
	else													//if the rests do not match
		v[4]=0;												//do not mark as price period for the firm
RESULT(v[4])


EQUATION("Firm_Desired_Markup")
/*
Firm Variable
*/
	v[11]=V("sector_price_frequency");
	v[0]=CURRENT;                                             						//strategic markup in the last period
	v[1]=V("Firm_Price_Period");                                         			//divides the time period by 8

	if(v[1]==1)                                                              		//if the rest of the above division is zero, adjust strategic markup
		{
		v[2]=VL("Firm_Avg_Potential_Markup",1);                                     //average potential markup of the firm in the last period        
		v[3]=V("sector_market_share_expansion");                                    //market-share expantion parameter
		v[4]=V("sector_markup_apropriation");                                       //profits apropriation parameter   
		v[5]=V("Firm_Desired_Market_Share");                                        //desired market-share 
		v[6]=VL("Firm_Avg_Market_Share",1);                                    		//firm average market share in the last period   
		v[7]=VL("Firm_Competitiveness",1);                                          //firm's competitiveness in the last period
		v[8]=VL("Sector_Avg_Competitiveness",1);                               		//sector's average competitiveness in the last period
		v[9]=v[3]*((v[7]-v[8])/v[8]);                                          		//how much to adjust based on the percentual diference between firm's competitiveness and sector's average competitiveness and the expantion parameter
		if(v[2]*(1+v[14])>v[0])                                      		//if the already adjusted average potential markup is higher than desired strategic markup of the last period and firm's average market share is higher than desired market share
			v[10]=v[0]+v[4]*(v[2]*(1+v[14])-v[0]);                              		//the firm adjusts the strategic markup. 
		else                                                                   		//if the adjusted average potential markup is not higher than desired nor the firm's average market-share is not higher than desired
			v[10]=v[0];                                                        		//strategic markup will be the last period's                                            
		
		v[12]=VL("Firm_Quality",1);
		v[13]=VL("Sector_Avg_Quality",1);
		if(v[13]!=0)
			v[14]=(v[12]-v[13])/v[13];
		else
			v[14]=0;
		v[21]=VL("Firm_Market_Share",1);
		v[22]=VL("Firm_Market_Share",v[11]+1);
		if(v[22]!=0)
			v[23]=(v[21]-v[22])/v[22];
		else
			v[23]=0;
		v[15]=v[0]*(1+v[4]*v[23]);		
		}
	else                                                                     		//if the rest of the above division is not zero, do not adjust strategic markup
		v[10]=v[0];                                                            		//strategic markup will be the last period's			
RESULT(v[10]) 


EQUATION("Firm_Wage")
/*
Nominal Wage of the firm. It increases year by year depending on inflation and firm's avg productivity. Passtrough parameters are sectorial.
*/
	v[0]=VL("Firm_Wage",1);                                                          	 //firm wage in the last period
	v[11]=V("annual_frequency");
	v[1]= fmod((double) t,v[11]);                                                        //divide the time period by the annual period parameter
	if(v[1]==0)                                                                      	 //if the rest of the above division is zero (beggining of the year, adjust wages)
		{
		v[2]=VL("Firm_Avg_Productivity", 1);                                           	 //firm average productivity in the last period
		v[3]=VL("Firm_Avg_Productivity", (v[11]+1));                                     //firm average productivity five periods befor
		v[4]=(v[2]-v[3])/v[3];                                                           //annual growth of sector average productivity
		v[5]=V("sector_passthrough_productivity");                                       //pass through of productivity to wages
		v[6]=VLS(GRANDPARENT, "Country_Consumer_Price_Index", 1);                        //price index in the last period
		v[7]=VLS(GRANDPARENT, "Country_Consumer_Price_Index", (v[11]+1));                //price index five periods before
		v[8]=max(0,((v[6]-v[7])/v[7])-v[21]);                                            //annual growth of price index (annual inflation)
		v[9]=V("sector_passthrough_inflation");                                          //pass through of inflation to wages   	
		v[12]=VL("Sector_Employment", 1);                                				 //sector employment in the last period
		v[13]=VL("Sector_Employment", (v[11]+1));                        				 //sector employment five periods before
		if(v[13]!=0)
			v[14]=(v[12]-v[13])/v[13];                                                   //annual growth of sector employment
		else
			v[14]=0;
		v[15]=V("sector_passthrough_employment");
		v[16]=VL("Sector_Capacity_Utilization", 1);
		v[17]=V("sector_desired_degree_capacity_utilization");
		v[18]=v[16]-v[17]>0?1:0;
		v[19]=V("sector_passthrough_capacity");
		v[20]=v[18]>0?1:0;
		v[21]=VS(financial, "target_inflation");
		v[22]=VLS(country, "Country_Annual_CPI_Inflation", 1);
		if(V("switch_cb_credibility")==1)
			v[23]=v[21];
		else
			v[23]=v[22];
		v[10]=v[0]*(1+v[23]+v[5]*v[4]+v[9]*(v[22]-v[21])+v[15]*v[20]+v[18]*v[19]);                      //current wage will be the last period's multiplied by a rate of growth which is an expected rate on productivity plus an inflation adjustment in the wage price index
		}
	else                                                                             	 //if the rest of the division is not zero, do not adjust wages
		v[10]=v[0];                                                                      //current wages will be the last period's
RESULT(v[10])


EQUATION("Firm_Variable_Cost")
/*
Variable unit cost is the wage cost (nominal wages over productivity) plus intermediate costs
*/
	v[4]=VLS(input, "Sector_Avg_Price",1);
	v[5]=V("sector_input_tech_coefficient");
	v[0]=v[4]*v[5];
	v[1]=V("Firm_Wage");
	v[2]=VL("Firm_Avg_Productivity",1);
	v[3]= v[2]!=0? (v[1]/v[2])+v[0] : v[0];
RESULT(v[3])


EQUATION("Firm_Unit_Financial_Cost")
/*
Financial costs include interest payment and debt payment. Unit financial cost is total financial costs divided by effective production.
*/
	v[0]=V("sector_investment_frequency");
	v[6]=V("sector_desired_degree_capacity_utilization");
	v[4]=0;
	for(i=1; i<=v[0]; i++)
		{
		v[1]=VL("Firm_Interest_Payment",i);
		v[2]=VL("Firm_Productive_Capacity",i);
			if(v[2]!=0)
				v[3]=v[1]/(v[2]*v[6]);
			else
				v[3]=0;
		v[4]=v[4]+v[3];
		}
	v[5]=v[4]/v[0];
	
	v[7]=VL("Firm_Debt_Rate",1);
	v[8]=VL("Firm_Desired_Debt_Rate",1);
	if(v[7]>v[8])
		v[9]=v[5];
	else
		v[9]=0;
RESULT(v[9])


EQUATION("Firm_Financial_Cost_Passtrough")
/*
1 if average market share is greater than desired and if debt rate is greater than desired, otherwise 0.
*/
	v[3]=VL("Firm_Debt_Rate",1);
	v[4]=VL("Firm_Desired_Debt_Rate",1);
	v[6]=V("sector_financial_cost_weight");
	if(v[3]>v[4])
		v[7]=v[6];
	else
		v[7]=0;
RESULT(v[7])


EQUATION("Firm_Desired_Price")
/*
Firm's desired price is a desired markup over variable costs.
*/
	v[0]=V("Firm_Desired_Markup");                         						//firm's desired markup
	v[1]=V("Firm_Variable_Cost");                          						//firm's variable cost 
	v[3]=V("Firm_Unit_Financial_Cost");
	v[4]=V("sector_financial_cost_passtrough");
	v[2]=v[0]*(v[1]+v[3]*v[4]);                                  				//firm's desired price will be the desired markup applied to labor cost plus inputs cost, labor cost defined as wages over productivity
RESULT(v[2])


EQUATION("Firm_Price")
/*
Firm's effective price is a average between the desired price and the sector average price
*/
	v[1]=V("Firm_Desired_Price");                                              //firm's desired price
	v[2]=V("sector_strategic_price_weight");                                   //strategic weight parameter
	v[3]=VL("Sector_Avg_Price", 1);                                            //sector average price in the last period
	v[4]=v[2]*(v[1])+(1-v[2])*(v[3]);                                          //firm's price is a average between the desired price and the sector average price
	v[5]=V("Firm_Price_Period");
	if(v[5]==1)
		v[6]=v[4];
	else
		v[6]=CURRENT;
RESULT(v[6])


EQUATION("Firm_Effective_Markup")
/*
Effective Markup is the Effective Price over the Variable Cost
*/
	v[0]=V("Firm_Price");
	v[1]=V("Firm_Variable_Cost");
	v[2]= v[1]!=0? v[0]/v[1] : 0;
RESULT(v[2])


EQUATION("Firm_Desired_Market_Share")
/*
Desired Market Share is a simple average between last period's desired market share and firm's average market share
*/
	v[1]=CURRENT;                        							//desired market share in the last period
	v[2]=VL("Firm_Avg_Market_Share", 1);                        	//firm's average market share (desired)
	v[3]=(v[1]+v[2])/2;                                         	//current desired market share is a simple average between last period's desired market share and firm's average market share
RESULT(max(v[1],v[3]))


EQUATION("Firm_Avg_Market_Share")
/*
Average Market Share between the market share of the firm in the last markup period
*/
	v[0]=V("sector_price_frequency");
	v[1]=0;										   						//initializes the sum
	for (i=1; i<=v[0]; i++)												//from 1 to markup period lags
		v[1]=v[1]+VL("Firm_Market_Share", i);							//sum up firm's lagged market share
	v[4]=v[1]/v[0];														//average firm's market share of the last investment period
RESULT(v[4])


EQUATION("Firm_Potential_Markup")
/*
Potential markup is the sector average price over firm's variable costs
*/
	v[0]=V("Sector_Avg_Price");                                       //sector average price
	v[1]=V("Firm_Variable_Cost");                                     //firm's variable cost
	v[2]= v[1]!=0? v[0]/v[1] : 0;                                     //potential markup is the sector average price over firm's variable costs
RESULT(v[2])


EQUATION("Firm_Avg_Potential_Markup")
/*
Average Potential Markup between the potential markup of the firm in the last 8 periods
*/
	v[0]=V("sector_price_frequency");
	v[1]=0;																//initializes the sum
	for (i=1; i<=v[0]; i++)												//from 1 to markup period lags
		v[1]=v[1]+VL("Firm_Potential_Markup", i);						//sum up firm's lagged potential markup
	v[4]=v[1]/v[0];														//average firm's market share of the last potential markup
RESULT(v[4])
