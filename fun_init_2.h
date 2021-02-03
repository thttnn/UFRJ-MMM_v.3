
EQUATION("Initialization_2")

consumption=SEARCH_CND("id_consumption_goods_sector",1);
capital=SEARCH_CND("id_capital_goods_sector",1);
input=SEARCH_CND("id_intermediate_goods_sector",1);
government=SEARCH("GOVERNMENT");
financial=SEARCH("FINANCIAL");
external=SEARCH("EXTERNAL_SECTOR");
country=SEARCH("COUNTRY");
centralbank=SEARCH("CENTRAL_BANK");

for (i=1 ; i<=V("annual_frequency")+1 ; i++)		              														
{
	WRITELLS(government, "Government_Effective_Expenses", VS(country,"initial_nominal_GDP")*VS(country,"initial_government_share_GDP"),0,i);
	WRITELLS(government, "Government_Debt", V("annual_frequency")*VS(country,"initial_nominal_GDP")*VS(government, "initial_government_debt_share_GDP"),0,i);
	WRITELLS(government, "Government_Debt_GDP_Ratio", VS(government, "initial_government_debt_share_GDP"),0,i);
}
WRITELLS(government, "Government_Max_Expenses", VS(country,"initial_nominal_GDP")*VS(country,"initial_government_share_GDP"),0,1);
WRITES(government, "Government_Interest_Payment", VL("Government_Debt",1)*(VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")));
WRITELLS(government, "Government_Surplus_Rate_Target", V("annual_frequency")*VS(government, "initial_government_debt_share_GDP")*(VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")),0,1);
WRITELLS(government, "Government_Total_Taxes", V("Government_Effective_Expenses")+V("Government_Interest_Payment"),0,1);
WRITELLS(government, "Government_Desired_Consumption", V("Government_Effective_Expenses")*VS(government, "government_initial_consumption_share"),0,1);
WRITES(government, "Government_Effective_Consumption", V("Government_Effective_Expenses")*VS(government, "government_initial_consumption_share"));
WRITELLS(government, "Government_Desired_Investment", V("Government_Effective_Expenses")*VS(government, "government_initial_capital_share"),0,1);
WRITES(government, "Government_Effective_Investment", V("Government_Effective_Expenses")*VS(government, "government_initial_capital_share"));
WRITELLS(government, "Government_Desired_Inputs", V("Government_Effective_Expenses")*VS(government, "government_initial_input_share"),0,1);
WRITES(government, "Government_Effective_Inputs", V("Government_Effective_Expenses")*VS(government, "government_initial_input_share"));
WRITELLS(government, "Government_Desired_Wages", V("Government_Effective_Expenses")*(1-VS(government, "government_initial_consumption_share")-VS(government, "government_initial_capital_share")-VS(government, "government_initial_input_share")),0,0);
WRITELLS(government, "Government_Effective_Wages", V("Government_Effective_Expenses")*(1-VS(government, "government_initial_consumption_share")-VS(government, "government_initial_capital_share")-VS(government, "government_initial_input_share")),0,0);

WRITELLS(external, "International_Reserves",  V("annual_frequency")*VS(country,"initial_nominal_GDP")*V("initial_international_reserves_GDP"),0,1);
WRITELLS(external, "External_Income",  VS(country,"initial_nominal_GDP")*VS(country,"initial_external_income_scale"),0,1);
WRITELLS(external, "External_Income",  VS(country,"initial_nominal_GDP")*VS(country,"initial_external_income_scale"),0,2);
WRITELLS(external, "Capital_Flows",  V("External_Income")*V("capital_flow_adjustment")*((VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation"))-V("external_interest_rate")),0,1);
WRITES(country, "Country_Nominal_Exports",  VS(country,"initial_nominal_GDP")*VS(country,"initial_exports_share_GDP"));
WRITES(country, "Country_Nominal_Imports", VS(country,"Country_Nominal_Exports")+VS(external,"Capital_Flows"));
WRITELLS(external, "Trade_Balance", VS(country,"Country_Nominal_Exports")-VS(country,"Country_Nominal_Imports"), 0, 1);
WRITES(consumption, "sector_nominal_exports", VS(country, "Country_Nominal_Exports")*VS(consumption, "sector_exports_share"));
WRITES(capital, "sector_nominal_exports", VS(country,"Country_Nominal_Exports")*VS(capital, "sector_exports_share"));
WRITES(input, "sector_nominal_exports", VS(country,"Country_Nominal_Exports")*VS(input, "sector_exports_share"));

WRITES(country, "Country_Total_Classes_Expenses", VS(country,"initial_nominal_GDP")*VS(country,"initial_consumption_share_GDP"));
WRITES(country, "Country_Total_Investment_Expenses", VS(country,"initial_nominal_GDP")*VS(country,"initial_investment_share_GDP"));
WRITES(country, "country_nominal_domestic_consumption", VS(country,"Country_Total_Classes_Expenses")-VS(external, "Country_Nominal_Imports"));

v[1]=(VS(government, "Government_Effective_Consumption")+VS(consumption, "sector_nominal_exports")+VS(country, "country_nominal_domestic_consumption"))/VS(consumption, "sector_initial_price");//consumption sector total real demand
v[2]=(VS(government, "Government_Effective_Investment")+VS(capital, "sector_nominal_exports")+VS(country, "Country_Total_Investment_Expenses"))/VS(capital, "sector_initial_price");//capital sector total real demand
v[3]=(v[1]*VS(consumption, "sector_input_tech_coefficient")+v[2]*VS(capital, "sector_input_tech_coefficient")+((VS(government, "Government_Effective_Inputs")+VS(input, "sector_nominal_exports"))/VS(input, "sector_initial_price")))/(1-VS(input, "sector_input_tech_coefficient"));//input sector total real demand
WRITES(consumption, "sector_initial_demand", v[1]);
WRITES(capital, "sector_initial_demand", v[2]);
WRITES(input, "sector_initial_demand", v[3]);

CYCLE(cur, "SECTORS")
  {
  v[4]=(VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")+VS(financial, "spread_long_term")+VS(financial, "risk_premium_long_term")*VS(cur, "sector_initial_debt_ratio"))*(VS(cur, "sector_initial_debt_ratio")*(1+VS(cur, "sector_liquidity_preference"))*VS(cur, "sector_capital_output_ratio")/VS(cur, "sector_desired_degree_capacity_utilization"));//sector unit interest payment
  v[5]=(VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")-VS(financial, "spread_deposits"))*(VS(cur, "sector_liquidity_preference")*VS(cur, "sector_capital_output_ratio")/VS(cur, "sector_desired_degree_capacity_utilization"));//sector unit interest receivment
  v[6]=VS(cur, "sector_initial_productivity")*(VS(cur, "sector_initial_price")*(1-VS(cur, "sector_indirect_tax_rate"))*(1-VS(cur, "sector_rnd_revenue_proportion"))-VS(cur, "sector_input_tech_coefficient")*VS(input, "sector_initial_price")+VS(capital, "sector_initial_price")*(v[5]-v[4])-VS(cur, "sector_profit_rate"));//sector unit nominal wage
  
  WRITES(cur, "Sector_Effective_Production", VS(cur, "sector_initial_demand"));
  WRITELLS(cur, "Sector_Productive_Capacity", VS(cur, "sector_initial_demand")/VS(cur, "sector_desired_degree_capacity_utilization"),0,1);
  WRITES(cur, "Sector_Stock_Deposits", VS(cur, "sector_liquidity_preference")*VS(cur, "Sector_Productive_Capacity")*VS(cur, "sector_capital_output_ratio")*VS(capital, "sector_initial_price"));
  WRITES(cur, "Sector_Stock_Loans", VS(cur, "sector_initial_debt_ratio")*(1+VS(cur, "sector_liquidity_preference"))*VS(cur, "Sector_Productive_Capacity")*VS(cur, "sector_capital_output_ratio")*VS(capital, "sector_initial_price"));
  for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                        		 								
		{
		WRITELLS(cur, "Sector_Avg_Quality", 1, 0, i);               							
		WRITELLS(cur, "Sector_Employment", VS(cur, "sector_initial_demand")/VS(cur, "sector_initial_productivity"), 0, i);               					
		WRITELLS(cur, "Sector_Avg_Price", VS(cur, "sector_initial_price"), 0, i);                                   		
		}
  WRITES(cur, "Sector_Sales", VS(cur, "sector_initial_demand"));
  WRITES(cur, "Sector_Taxation", VS(cur, "sector_initial_demand")*VS(cur, "sector_initial_price")*VS(cur, "sector_indirect_tax_rate"));
  WRITES(cur, "sector_rnd_expenses", VS(cur, "sector_initial_demand")*VS(cur, "sector_initial_price")*(1-VS(cur, "sector_indirect_tax_rate"))*VS(cur, "sector_rnd_revenue_proportion"));
  WRITES(cur, "sector_interest_payment", v[4]*VS(cur, "sector_initial_demand"));
  WRITES(cur, "sector_interest_receivment", v[5]*VS(cur, "sector_initial_demand"));
  WRITES(cur, "sector_wage_payment", VS(cur, "sector_initial_demand")*v[6]/VS(cur, "sector_initial_productivity"));
  WRITES(cur, "sector_net_profits", VS(cur, "sector_initial_demand")*VS(cur, "sector_profit_rate"));
  v[11]= VS(capital, "sector_initial_price")*(VS(cur, "sector_number_object_firms")/VS(cur, "sector_investment_frequency"));
  v[10]= v[11]/VS(capital, "sector_initial_price");
  LOG("\nSector Capital Demand %f.",v[10]);
  WRITES(cur, "sector_retained_profits", v[11]-(VS(cur,"Sector_Stock_Loans")/VS(cur, "sector_amortization_period")));
  WRITES(cur, "sector_distributed_profits", VS(cur,"sector_net_profits")-VS(cur,"sector_retained_profits"));
  WRITES(cur, "sector_profits_distribution_rate", (VS(cur,"sector_net_profits")-VS(cur,"sector_retained_profits"))/VS(cur,"sector_net_profits"));
   for (i=1 ; i<=VS(cur, "sector_investment_frequency"); i++)															
		{
		WRITELLS(cur, "Sector_Demand_Met", 1, 0, i); 										 
		WRITELLS(cur, "Sector_Demand_Met_By_Imports", 1, 0, i);                      			
		WRITELLS(cur, "Sector_Effective_Orders", VS(cur, "sector_initial_demand"), 0, i);               					
		}
	WRITELLS(cur, "Sector_Productive_Capacity_Available", 0, 0, 1);                  	
	WRITELLS(cur, "Sector_Avg_Competitiveness", 1, 0, 1);                     				
	WRITELLS(cur, "Sector_External_Price", VS(cur, "sector_initial_price"), 0, 1);                               	
	WRITELLS(cur, "Sector_Avg_Productivity", VS(cur, "sector_initial_productivity"), 0,  1);               	 				
	WRITELLS(cur, "Sector_Max_Productivity", VS(cur, "sector_initial_productivity"), 0,  1);                      			
	WRITELLS(cur, "Sector_Max_Quality", 1, 0, 1);
	WRITELLS(cur, "Sector_Inventories", VS(cur, "sector_initial_demand")*VS(cur, "sector_desired_inventories_proportion"), 0, 1);                  										
	WRITELLS(cur, "Sector_Real_Exports", VS(cur, "sector_nominal_exports")/VS(cur, "sector_initial_price"), 0, 1);	
	
	cur1=SEARCHS(cur, "FIRMS");																			
	WRITES(cur1, "firm_date_birth", 0);                                   					
	for (i=1 ; i<=VS(cur, "sector_investment_frequency") ; i++)                                									
	  	{
	  	WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Replacement", 0, 0, i);					
	  	WRITELLS(cur1, "Firm_Debt_Rate", VS(cur, "sector_initial_debt_ratio"), 0, i);												
	  	WRITELLS(cur1, "Firm_Demand_Capital_Goods", 0, 0, i);
	  	WRITELLS(cur1, "Firm_Frontier_Productivity", VS(cur, "sector_initial_productivity"), 0, i);                 		
	  	WRITELLS(cur1, "Firm_Max_Productivity", VS(cur, "sector_initial_productivity"), 0, i);        							
	  	WRITELLS(cur1, "Firm_Avg_Productivity", VS(cur, "sector_initial_productivity"), 0, i);									
		WRITELLS(cur1, "Firm_Capacity_Utilization", VS(cur, "sector_desired_degree_capacity_utilization"), 0, i);
		}
	for(i=1; i<=VS(cur, "sector_investment_frequency")+1; i++)										 							
		{
		WRITELLS(cur1, "Firm_Productive_Capacity_Depreciation", 0, 0, i);  						
		WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Expansion", 0, 0, i);     				
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Expansion", 0, 0, i);     					
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Replacement", 0, 0, i);     					
		WRITELLS(cur1, "Firm_Effective_Orders_Capital_Goods", 0, 0, i);  						 
		}
	for (i=1 ; i<=2*VS(cur, "sector_investment_frequency") ; i++)																
	  	WRITELLS(cur1, "Firm_Effective_Orders", VS(cur, "sector_initial_demand")/VS(cur, "sector_number_object_firms"), 0, i);                    		
		WRITELLS(cur1, "Firm_Effective_Market_Share", 1/VS(cur, "sector_number_object_firms"), 0, 1);  
		WRITELLS(cur1, "Firm_Desired_Market_Share", 1/VS(cur, "sector_number_object_firms"), 0, 1);                  		
		WRITELLS(cur1, "Firm_Avg_Market_Share", 1/VS(cur, "sector_number_object_firms"), 0, 1);                     			
		WRITELLS(cur1, "Firm_Price", VS(cur, "sector_initial_price"), 0, 1);                                      					
		WRITELLS(cur1, "Firm_Sales", VS(cur, "sector_initial_demand")/VS(cur, "sector_number_object_firms"), 0, 1);									
		WRITELLS(cur1, "Firm_Revenue", VS(cur, "sector_initial_price")*VS(cur, "sector_initial_demand")/VS(cur, "sector_number_object_firms"), 0, 1);                           
		WRITELLS(cur1, "Firm_Stock_Inventories", VS(cur, "sector_desired_inventories_proportion")*VS(cur, "sector_initial_demand")/VS(cur, "sector_number_object_firms"), 0, 1);               
		WRITELLS(cur1, "Firm_Stock_Inputs", VS(cur, "sector_input_tech_coefficient")*VS(cur, "sector_initial_demand")/VS(cur, "sector_number_object_firms"), 0, 1);                    			
		WRITELLS(cur1, "Firm_Productive_Capacity", VS(cur, "Sector_Productive_Capacity")/VS(cur, "sector_number_object_firms"), 0, 1);						
		WRITELLS(cur1, "Firm_Capital", VS(cur, "Sector_Productive_Capacity")*VS(cur, "sector_capital_output_ratio")*VS(capital, "sector_initial_price")/VS(cur, "sector_number_object_firms"), 0, 1);									
		WRITELLS(cur1, "Firm_Wage", v[6], 0, 1); 												
		WRITELLS(cur1, "Firm_Variable_Cost", (v[6]/VS(cur, "sector_initial_productivity"))+VS(input, "sector_initial_price")*VS(cur, "sector_input_tech_coefficient"), 0, 1);	
		WRITELLS(cur1, "Firm_Avg_Potential_Markup", VS(cur, "sector_initial_price")/VS(cur, "Firm_Variable_Cost"), 0, 1);								
		WRITELLS(cur1, "Firm_Desired_Markup", VS(cur, "sector_initial_price")/VS(cur, "Firm_Variable_Cost"), 0, 1); 					
		WRITELLS(cur1, "Firm_Competitiveness", 1, 0, 1);                           				
		WRITELLS(cur1, "Firm_Delivery_Delay", 1, 0, 1);                           		  		
		WRITELLS(cur1, "Firm_Stock_Deposits", VS(cur,"Sector_Stock_Deposits")/VS(cur, "sector_number_object_firms"), 0, 1);											
		WRITELLS(cur1, "Firm_Stock_Loans", VS(cur,"Sector_Stock_Loans")/VS(cur, "sector_number_object_firms"), 0, 1);                       
	  	WRITELLS(cur1, "Firm_Avg_Debt_Rate", VS(cur, "sector_initial_debt_ratio"), 0, 1);                       				
	  	WRITELLS(cur1, "Firm_Desired_Debt_Rate", VS(cur, "sector_initial_debt_ratio"), 0, 1);                       			
	  	WRITELLS(cur1, "Firm_Liquidity_Preference", VS(cur, "sector_liquidity_preference"), 0, 1);                       		
		for (i=1 ; i<=VS(cur,"sector_price_frequency")+1 ; i++)																
			{
			WRITELLS(cur1, "Firm_Market_Share", 1/VS(cur, "sector_number_object_firms"), 0, i);             						
			WRITELLS(cur1, "Firm_Potential_Markup", VS(cur, "sector_initial_price")/VS(cur, "Firm_Variable_Cost"), 0, i);                      			
			}	
	
	  		cur2=SEARCHS(cur1, "CAPITALS");														
	  		WRITELLS(cur2, "Capital_Good_Acumulated_Production", 0, 0, 1);      				
			WRITES(cur2, "capital_good_productive_capacity", 1/VS(cur,"sector_capital_output_ratio"));     					
			WRITES(cur2, "capital_good_productivity_initial", VS(cur,"sector_initial_productivity"));       		  		
			WRITES(cur2, "capital_good_to_replace", 0);
			WRITES(cur2, "id_capital_good_number", 1); 
			WRITES(cur2, "capital_good_date_birth", 0);										
			WRITES(cur2, "capital_good_depreciation_period", uniform_int(30, 60));  
		
		for(i=1; i<=VS(cur, "sector_number_object_firms")-1; i++)															
			cur4=ADDOBJ_EXLS(cur,"FIRMS", cur1, 0);                             					
		CYCLES(cur, cur1, "FIRMS")                                                 			
			{													
			WRITES(cur1, "id_firm_number", SEARCH_INSTS(cur, cur1));                         					
			v[25]=SEARCH_INSTS(cur, cur1)/(VS(cur, "sector_number_object_firms")/VS(financial, "number_object_banks"));
			v[26]=round(v[25]);
			v[27]= v[26]<v[25]? v[26]+1 : v[26];
			WRITES(cur1, "id_firm_bank", v[27]);
			v[31]=fmod((double) (SEARCH_INSTS(cur, cur1)+VS(cur, "sector_investment_frequency")), VS(cur, "sector_investment_frequency"));     
				
			for(i=1; i<=(VS(cur, "sector_initial_demand")/VS(cur, "sector_desired_degree_capacity_utilization"))*VS(cur, "sector_capital_output_ratio")/VS(cur, "sector_number_object_firms"); i++)                        						
				{                                     			
				cur3=ADDOBJ_EXLS(cur1,"CAPITALS", SEARCHS(cur1, "CAPITALS"), 0);			                       			
				WRITES(cur3, "id_capital_good_number", (i+1));									
				}	
				v[20]=fmod(VS(cur1, "id_firm_number")+VS(cur, "sector_investment_frequency"), VS(cur, "sector_investment_frequency"));
				CYCLES(cur1, cur3, "CAPITALS")
					WRITES(cur3, "capital_good_depreciation_period", v[20]+(VS(cur3,"id_capital_good_number")-1)*VS(cur, "sector_investment_frequency"));
					
			WRITELLS(cur1, "Firm_Productive_Capacity", SUMS(cur1, "capital_good_productive_capacity"), 0, 1);	
			for (i=1 ; i<=VS(cur, "sector_investment_frequency") ; i++)
				WRITELLS(cur1, "Firm_Capacity_Utilization", VS(cur1, "Firm_Effective_Orders")/VS(cur1,"Firm_Productive_Capacity"), 0, i);	
			}
  //WRITELLS(cur, "Sector_Productive_Capacity", SUMLS(cur, "Firm_Productive_Capacity",1),0,1);
  //WRITES(cur, "sector_desired_degree_capacity_utilization", AVELS(cur, "Firm_Capacity_Utilization",1));	                    						 												
  }
  
WRITES(financial, "Financial_Sector_Total_Stock_Loans", SUMS(country,"Sector_Stock_Loans"));
WRITES(financial, "Financial_Sector_Stock_Deposits", SUMS(country,"Sector_Stock_Loans")*VS(financial, "initial_bank_levarage"));
WRITES(financial, "total_stock_deposits_firms", SUMS(country,"Sector_Stock_Deposits"));
WRITES(financial, "total_stock_deposits_classes", max(0,V("Financial_Sector_Stock_Deposits")-V("total_stock_deposits_firms")));
WRITES(financial, "Financial_Sector_Interest_Receivment", SUMS(country,"sector_interest_payment"));
WRITES(financial, "Financial_Sector_Interest_Payment", V("Financial_Sector_Stock_Deposits")*(VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")-VS(financial, "spread_deposits")));
WRITES(financial, "Financial_Sector_Profits", V("Financial_Sector_Interest_Receivment")+VS(government, "Government_Interest_Payment")-V("Financial_Sector_Interest_Payment"));
WRITES(financial, "Financial_Sector_Accumulated_Profits", V("Financial_Sector_Total_Stock_Loans")*VS(financial, "minimum_capital_ratio"));
WRITES(financial, "Financial_Sector_Distributed_Profits", V("Financial_Sector_Profits"));
WRITELLS(financial, "Basic_Interest_Rate", VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation"), 0, 1);
WRITELLS(financial, "Avg_Competitiveness_Financial_Sector", 1, 0, 1);
WRITELLS(financial, "Avg_Interest_Rate_Long_Term", VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")+VS(financial, "spread_short_term"), 0, 1);
WRITELLS(financial, "Avg_Interest_Rate_Short_Term", VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation")+VS(financial, "spread_long_term"), 0, 1);

for(i=1; i<=VS(financial, "number_object_banks")-1; i++)																
	cur=ADDOBJ_EXLS(financial,"BANKS", SEARCHS(financial, "BANKS"), 0);
	CYCLES(financial, cur, "BANKS")                                                 				
		{													
		WRITES(cur, "id_bank", SEARCH_INSTS(root, cur)); 
		WRITELLS(cur, "Bank_Market_Share", 1/VS(financial, "number_object_banks"), 0, 1); 
		WRITELLS(cur, "Bank_Competitiveness", 1, 0, 1);
		WRITELLS(cur, "Bank_Accumulated_Profits", VS(financial, "Financial_Sector_Accumulated_Profits")/VS(financial, "number_object_banks"), 0, 1);
		WRITELLS(cur, "Bank_Demand_Met", 1, 0, 1);
		WRITELLS(cur, "Bank_Desired_Long_Term_Spread", VS(financial, "spread_long_term"), 0, 1);
		WRITELLS(cur, "Bank_Desired_Short_Term_Spread", VS(financial, "spread_short_term"), 0, 1);
		WRITELLS(cur, "Bank_Interest_Rate_Long_Term", VS(financial, "Avg_Interest_Rate_Long_Term"), 0, 1);
		WRITELLS(cur, "Bank_Interest_Rate_Short_Term", VS(financial, "Avg_Interest_Rate_Short_Term"), 0, 1);
		}
  
WRITES(country, "Country_Total_Wages", SUM("sector_wage_payment")+SUM("sector_rnd_expenses")+VS(government, "Government_Effective_Wages"));
WRITES(country, "Country_Total_Profits", SUM("sector_net_profits")+VS(financial, "Financial_Sector_Profits"));
WRITES(country, "Country_Distributed_Profits", (SUM("sector_net_profits")-SUM("sector_retained_profits"))+VS(financial, "Financial_Sector_Distributed_Profits"));

WRITES(government, "Government_Indirect_Taxes", SUMS(country,"Sector_Taxation"));
WRITES(government, "Government_Income_Taxes", V("Government_Total_Taxes")-V("Government_Indirect_Taxes"));

CYCLE(cur, "CLASSES")
	{
	WRITES(cur, "Class_Nominal_Gross_Income", VS(country, "Country_Total_Wages")+VS(country, "Country_Distributed_Profits"));
	WRITES(cur, "Class_Income_Share", VS(cur, "Class_Nominal_Gross_Income")/(VS(country, "Country_Distributed_Profits")+VS(country,"Country_Total_Wages")));
	WRITES(cur, "class_direct_tax", VS(government, "Government_Income_Taxes")/(VS(country, "Country_Distributed_Profits")+VS(country,"Country_Total_Wages")));
	WRITES(cur, "Class_Taxation", VS(cur, "class_direct_tax")*VS(cur,"Class_Nominal_Gross_Income"));
	for (i=1 ; i<=V("annual_frequency") ; i++)
	{
		WRITELLS(cur, "Class_Nominal_Disposable_Income", VS(cur,"Class_Nominal_Gross_Income")-VS(cur, "Class_Taxation"),0,i);
		WRITELLS(cur, "Class_Real_Disposable_Income", VS(cur,"Class_Nominal_Disposable_Income")/VS(consumption, "sector_initial_price"),0,i);
	}
	WRITELLS(cur, "Class_Avg_Nominal_Income", VS(cur,"Class_Nominal_Gross_Income")-VS(cur, "Class_Taxation"),0,1);
	WRITELLS(cur, "Class_Avg_Real_Income", VS(cur,"Class_Nominal_Disposable_Income")/VS(consumption, "sector_initial_price"),0,1);
	WRITES(cur, "Class_Effective_Expenses", VS(cur, "Country_Total_Classes_Expenses"));
	WRITES(cur, "Class_Effective_Real_Domestic_Consumption", VS(country, "country_nominal_domestic_consumption")*VS(cur, "Class_Income_Share")/VS(consumption,"sector_initial_price"));
	WRITES(cur, "Class_Effective_Real_Imported_Consumption", VS(external, "Country_Nominal_Imports")*VS(cur, "Class_Income_Share")/VS(consumption,"sector_initial_price"));
	WRITES(cur, "class_propensity_to_import", VS(cur, "Class_Effective_Real_Imported_Consumption")/(VS(cur,"Class_Nominal_Disposable_Income")/VS(consumption, "sector_initial_price")));
	WRITES(cur, "class_propensity_to_consume", 0.9*VS(cur, "Class_Effective_Real_Domestic_Consumption")/(VS(cur,"Class_Nominal_Disposable_Income")/VS(consumption, "sector_initial_price")));
	
	WRITELLS(cur, "Class_Real_Autonomous_Consumption", 0.1*VS(cur, "Class_Effective_Real_Domestic_Consumption")/VS(consumption, "sector_initial_price"), 0, 1);         			
	WRITELLS(cur, "Class_Liquidity_Preference", VS(cur,"initial_class_liquidity_preference"), 0, 1);
	WRITELLS(cur, "Class_Desired_Debt_Rate", VS(cur,"initial_class_desired_debt_rate"), 0, 1);
	WRITELLS(cur, "Class_Debt_Rate", 0, 0, 1);                              			
	WRITELLS(cur, "Class_Stock_Deposits", 0, 0, 1);
	}

WRITELLS(country,"Country_Annual_Growth", 0, 0, 1);													
WRITELLS(country,"Country_Annual_Real_Growth", 0, 0, 1);                 						
WRITELLS(country,"Country_Annual_Inflation", 0, 0, 1);	
for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                  											
		{
		WRITELLS(country,"Country_Price_Index", WHTAVE("sector_initial_price", "sector_initial_demand")/SUM("sector_initial_demand"), 0, i);					
		WRITELLS(country,"Country_Consumer_Price_Index", VS(consumption, "sector_initial_price"), 0, i);          							
		WRITELLS(country,"Country_Capital_Goods_Price", VS(capital, "sector_initial_price"), 0, i);
		WRITELLS(country,"Country_Avg_Productivity", WHTAVE("sector_initial_productivity", "Sector_Employment")/SUMS(country, "Sector_Employment"), 0, i);
		}
for (i=1 ; i<=(2*V("annual_frequency")) ; i++)                  											
		{
		WRITELLS(country,"Country_GDP", VS(country,"initial_nominal_GDP"), 0, i);                     	 								
		WRITELLS(country,"Country_Real_GDP", VS(country,"initial_nominal_GDP")/V("Country_Price_Index"), 0, i);                  						
		}
	
	
PARAMETER
RESULT(0)