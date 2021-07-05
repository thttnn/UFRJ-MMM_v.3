/*****GOVERNMENT DECISION VARIABLES*****/


EQUATION("Government_Desired_Wages")
/*
Priority expenses.
If there are no maximum expenses, it is adjusted by average productivity growth and inflation.
*/     
	v[0]=V("annual_frequency");								
	v[1]=LAG_GROWTH(country, "Country_Consumer_Price_Index", v[0], 1);		   		
	v[2]=V("government_real_annual_wage_growth");
	v[3]= fmod((double) t-1,v[0]);
	if(v[3]==0)
		v[4]=CURRENT*v[0]*(1+v[2]+v[1]);
	else
		v[4]=CURRENT*v[0];
	v[5]=v[4]/v[0];
RESULT(max(0,v[5]))


EQUATION("Government_Desired_Unemployment_Benefits")
/*
Counter-cyclical Expenses
Benefit is a share of average wage. 
The amount depends on current unemployment.
*/
	v[0]=V("government_benefit_rate");
	v[1]=0;
	CYCLES(country, cur, "SECTORS")
	{
		v[2]=VS(cur, "sector_desired_degree_capacity_utilization");
		v[3]=VLS(cur, "Sector_Idle_Capacity", 1);
		v[4]=v[3]-(1-v[2]);
		v[5]=VLS(cur, "Sector_Productive_Capacity", 1);
		v[6]=v[4]*v[5];
		v[7]=VLS(cur, "Sector_Avg_Productivity", 1);
		v[8]=VLS(cur, "Sector_Avg_Wage", 1);
		v[9]=v[6]*(v[0]*v[8]/v[7]);
		v[1]=v[1]+v[9];
	}
	
	v[1]=0;
	CYCLES(country, cur, "SECTORS")
	{
		v[2]=VLS(cur, "Sector_Employment",1);
		v[3]=VLS(cur, "Sector_Employment",2);
		v[4]=-(v[2]-v[3]);
		v[5]=max(0, v[4]);
		v[8]=VLS(cur, "Sector_Avg_Wage", 1);
		v[9]=v[5]*(v[0]*v[8]);
		v[1]=v[1]+v[9];
	}	
RESULT(max(0,v[1]))


EQUATION("Government_Desired_Investment")
/*
Desired Investment Expenses
Adjusted by a desired real growth rate and avg capital price growth
*/
	v[0]=V("annual_frequency");								
	v[1]=LAG_GROWTH(capital, "Sector_Avg_Price", v[0], 1);		   		
	v[2]=V("government_real_annual_investment_growth");
	v[3]= fmod((double) t-1,v[0]);
	if(v[3]==0)
		v[4]=CURRENT*v[0]*(1+v[2]+v[1]);
	else
		v[4]=CURRENT*v[0];
	v[5]=v[4]/v[0];
RESULT(max(0,v[5]))


EQUATION("Government_Desired_Consumption")
/*
Desired Consumption Expenses
Adjusted by a desired real growth rate and avg consumption price growth
*/
	v[0]=V("annual_frequency");								
	v[1]=LAG_GROWTH(consumption, "Sector_Avg_Price", v[0], 1);		   		
	v[2]=V("government_real_annual_consumption_growth");
	v[3]= fmod((double) t-1,v[0]);
	if(v[3]==0)
		v[4]=CURRENT*v[0]*(1+v[2]+v[1]);
	else
		v[4]=CURRENT*v[0];
	v[5]=v[4]/v[0];
RESULT(max(0,v[5]))


EQUATION("Government_Desired_Inputs")
/*
Desired Intermediate Expenses
Adjusted by a desired real growth rate and avg input price growth
*/
	v[0]=V("annual_frequency");								
	v[1]=LAG_GROWTH(input, "Sector_Avg_Price", v[0], 1);		   		
	v[2]=V("government_real_annual_input_growth");
	v[3]= fmod((double) t-1,v[0]);
	if(v[3]==0)
		v[4]=CURRENT*v[0]*(1+v[2]+v[1]);
	else
		v[4]=CURRENT*v[0];
	v[5]=v[4]/v[0];
RESULT(max(0,v[5]))


/*****FISCAL RULES VARIABLES*****/


EQUATION("Government_Surplus_Rate_Target")
/*
Adjusts government surplus target based on debt to gdp evolution
*/
	v[0]=V("annual_frequency");
	v[1]=V("government_max_surplus_target");                     
	v[2]=V("government_min_surplus_target");
	v[3]=LAG_GROWTH(p, "Government_Debt_GDP_Ratio", v[0], 1);
	v[4]=LAG_AVE(p,"Government_Debt_GDP_Ratio",v[0],1);        //annual average debt rate
	v[5]=V("government_max_debt_ratio");                       //maximum debt to gdp accepted, parameter
	v[6]=V("government_min_debt_ratio");                       //minimum debt to gdp accepted, parameter
	v[7]=V("government_surplus_target_adjustment");			   //adjustment parameter
	v[8]=V("begin_flexible_surplus_target");
	
	v[9]= fmod((double) t-1,v[0]);
	if(t>=v[8]&&v[8]!=-1&&v[9]==0)
	{
	if(v[4]>v[5])                           		   								 //if debt to gdp is higher than accepted 
		v[10]=CURRENT+v[7];
	else if (v[4]<v[6])                     		  								 //if debt to gdp is lower than accepted 
		v[10]=CURRENT-v[7];
	else
	{		//if debt to gdp is between acceptable band
		if(v[3]>0)
			v[10]=CURRENT+v[7];
		if(v[3]<0)
			v[10]=CURRENT-v[7];
		else
			v[10]=CURRENT;
	}
	}
	else                                               								 //if flexible surplus target rule is not active
		v[10]=CURRENT;                                    							 //do not change surplus taget  
		
	v[11]=max(min(v[1],v[10]),v[2]);
RESULT(v[11])


EQUATION("Government_Max_Expenses_Surplus")
/*
Government Max Expenses determined by Primary Surplus Target Fiscal rule
*/
	v[0]=V("annual_frequency");
	v[1]= fmod((double) t-1,v[0]);
	if(v[1]==0)
	{
		v[2]=LAG_SUM(country, "Country_GDP", v[0], 1);
		v[3]=LAG_SUM(country, "Country_GDP", v[0], v[0]+1);
		v[4]=V("government_expectations");
		v[5]=v[3]!=0? v[4]*(v[2]-v[3])/v[3] : 0;
		v[6]=LAG_SUM(government, "Government_Total_Taxes", v[0], 1);
		v[7]=V("Government_Surplus_Rate_Target");
		v[8]=(1+v[5])*(v[6]-v[7]*v[2]);
		v[9]=v[8]/v[0];
	}
	else
		v[9]=CURRENT;
RESULT(v[9])


EQUATION("Government_Max_Expenses_Ceiling")
/*
Government Max Expenses determined by Expenses Ceiling Target Fiscal rule
*/
	v[0]=V("annual_frequency");
	v[1]= fmod((double) t-1,v[0]);
	if(v[1]==0)
		{
		v[2]=LAG_GROWTH(consumption, "Country_Consumer_Price_Index", v[0], 1);
		v[3]=LAG_SUM(government, "Government_Effective_Expenses", v[0], 1);
		v[4]=v[3]*(1+v[2])/v[0];
		}
	else
		v[4]=CURRENT;
RESULT(v[4])


EQUATION("Government_Max_Expenses")
/*
Maximum Government expenses imposed by the fiscal rule.
Fiscal rules can be two types: primary surplus target or expenses ceiling (or both).
Depend on the policy parameter.
*/

v[1]=V("begin_surplus_target_rule");                           //define when surplus target rule begins
v[2]=V("begin_expenses_ceiling_rule");                         //define when expenses ceiling begins
																	
v[3]=V("Government_Max_Expenses_Surplus");
v[4]=V("Government_Max_Expenses_Ceiling");

	if ((t>=v[1]&&v[1]!=-1)&&(t>=v[2]&&v[2]!=-1))
		v[5]=min(v[3],v[4]);												//surplus rule and ceiling rule
	else if ((t>=v[1]&&v[1]!=-1)&&(t<v[2]||v[2]==-1))
		v[5]=v[3];															//only surplus rule
	else if ((t<v[1]||v[1]==-1)&&(t>=v[2]&&v[2]!=-1))
		v[5]=v[4];															//only ceiling rule
	else
		v[5]=-1;															//no rule															
RESULT(v[5])


EQUATION("Government_Effective_Expenses")
/*
Priority expenses.
If there are no maximum expenses, it is adjusted by average productivity growth and inflation.

switch_government_composition: Determines the composition and priority of government expenses, and initial distribution
0--> Government Wages(100%) [Only Public Workers]
1--> Government Wages(100%) + Unemployment Benefits(0%) [Public Workers and Unemployment Benefits]
2--> Government Wages(1-(c+k+i)%) + Unemployment Benefits(0%) + Government Consumption (c%), Investment(k%) and Intermediate Demand(i%) [Public Workers, Unemployment Benefits, and Demand to Sectors]

government_initial_consumption_share
government_initial_capital_share
government_initial_input_share
government_initial_benefits_share (zero by hypothesis)
those parameters can be used to exclude one or more types of goods, for instance.

*/

v[0]=V("Government_Max_Expenses");
v[1]=V("Government_Desired_Wages");
v[2]=V("Government_Desired_Unemployment_Benefits");
v[3]=V("Government_Desired_Consumption");
v[4]=V("Government_Desired_Inputs");
v[5]=V("Government_Desired_Investment");
v[6]=v[1]+v[2]+v[3]+v[4]+v[5];							   //total desired expenses

if(v[0]==-1)                                               //no fiscal rule
{
	v[16]=v[1];											   //government wages equal desired wages
	v[17]=v[2];    										   //government unemployment benefits equal 0
	v[18]=v[3];                                            //government consumption equal desired
	v[19]=v[4];                                            //government intermediate equal desired
	v[20]=v[5];                                            //government investment demand equals desired
}
else
{
	v[7]=V("switch_government_priority_scheme");
	
	if(v[7]==0)//no priority, effective expenses are proportional to desired. No seed for switch_extra_gov_expenses
		{
		v[8]= v[6]!=0? v[0]*v[1]/v[6] : 0;								
		v[9]= v[6]!=0? v[0]*v[2]/v[6] : 0;								
		v[10]=v[6]!=0? v[0]*v[3]/v[6] : 0;								
		v[11]=v[6]!=0? v[0]*v[4]/v[6] : 0;								
		v[12]=v[6]!=0? v[0]*v[5]/v[6] : 0;								
		}
	if(v[7]==1)//wages and benefits are compulsory. The rest is divided proportionally.
		{
		v[8]=min(v[0],v[1]);														 
		v[9]=min(v[2],(v[0]-v[8]));    												 
		v[10]=(v[3]+v[4]+v[5])!=0? (v[0]-v[8]-v[9])*v[3]/(v[3]+v[4]+v[5]) : 0;		 
		v[11]=(v[3]+v[4]+v[5])!=0? (v[0]-v[8]-v[9])*v[4]/(v[3]+v[4]+v[5]) : 0;		
		v[12]=(v[3]+v[4]+v[5])!=0? (v[0]-v[8]-v[9])*v[5]/(v[3]+v[4]+v[5]) : 0;		
		}
	if(v[7]==2)//wages->benefits->consumption->inputs->investment
		{
		v[8]=min(v[0],v[1]);								   
		v[9]=min(v[2],(v[0]-v[8]));    						 
		v[10]=min(v[3],(v[0]-v[8]-v[9]));       			 
		v[11]=min(v[4],(v[0]-v[8]-v[9]-v[10]));        		 
		v[12]=min(v[5],(v[0]-v[8]-v[9]-v[10]-v[11]));         
		}
		
	v[14]=max(0,(v[0]-(v[8]+v[9]+v[10]+v[11]+v[12])));		   //available government expenses		   
	v[15]=V("switch_extra_gov_expenses");
	if(v[15]==0)//no extra expenses
		{
		v[16]=v[8];
		v[17]=v[9];
		v[18]=v[10];
		v[19]=v[11];
		v[20]=v[12];
		}
	if(v[15]==1)//extra wages
		{
		v[16]=v[8]+v[14];
		v[17]=v[9];
		v[18]=v[10];
		v[19]=v[11];
		v[20]=v[12];
		}
	if(v[15]==2)//extra discritionary expenses, divided proportionally
		{
		v[16]= v[8];
		v[17]= v[9];
		v[18]= (v[3]+v[4]+v[5])!=0? v[10]+(v[14]*v[3]/(v[3]+v[4]+v[5])) : 0;
		v[19]= (v[3]+v[4]+v[5])!=0? v[11]+(v[14]*v[4]/(v[3]+v[4]+v[5])) : 0;
		v[20]= (v[3]+v[4]+v[5])!=0? v[12]+(v[14]*v[5]/(v[3]+v[4]+v[5])) : 0;
		}
	if(v[15]==3)//extra investment
		{
		v[16]=v[8];
		v[17]=v[9];
		v[18]=v[10];
		v[19]=v[11];
		v[20]=v[12]+v[14];
		}				
}
WRITE("Government_Effective_Wages", max(0,v[16]));
WRITE("Government_Effective_Unemployment_Benefits",  max(0,v[17]));
WRITE("Government_Effective_Consumption",  max(0,v[18]));
WRITE("Government_Effective_Inputs",  max(0,v[19]));
WRITE("Government_Effective_Investment",  max(0,v[20]));
WRITE("Government_Desired_Expenses",  v[6]);
v[21]=max(0,(v[16]+v[17]+v[18]+v[19]+v[20]));
RESULT(v[21])

EQUATION_DUMMY("Government_Effective_Wages","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Unemployment_Benefits","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Consumption","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Investment","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Inputs","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Desired_Expenses","Government_Effective_Expenses")

/*****GOVERNMENT RESULT VARIABLES*****/


EQUATION("Government_Income_Taxes")
RESULT(SUMS(country,"Class_Taxation"))

EQUATION("Government_Indirect_Taxes")
RESULT(SUMS(country,"Sector_Taxation"))

EQUATION("Government_Total_Taxes")
RESULT(V("Government_Income_Taxes")+V("Government_Indirect_Taxes"))

EQUATION("Government_Primary_Result")
RESULT(V("Government_Total_Taxes")-V("Government_Effective_Expenses"))

EQUATION("Government_Interest_Payment")
RESULT(V("Central_Bank_Basic_Interest_Rate")*max(0,VL("Government_Debt",1)))

EQUATION("Government_Nominal_Result")
RESULT(V("Government_Primary_Result")-V("Government_Interest_Payment"))

EQUATION("Government_Debt")
RESULT(CURRENT-V("Government_Nominal_Result")+VS(financial, "Financial_Sector_Rescue"))

EQUATION("Government_Debt_GDP_Ratio")
	v[1]=V("Government_Debt");
	v[2]=LAG_SUM(country, "Country_GDP", V("annual_frequency"));
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])

EQUATION("Government_Surplus_GDP_Ratio")
	v[1]=V("Government_Primary_Result");
	v[2]=V("Country_GDP");
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])

EQUATION("Government_Fiscal_Multiplier")
	v[0]=LAG_GROWTH(p, "Government_Effective_Expenses",V("annual_frequency"));
	v[1]=LAG_GROWTH(country, "Country_GDP",V("annual_frequency"));
	v[2]= fmod((double) t-1,V("annual_frequency"));
	if(v[2]==0)
		v[3]= v[0]!=0? v[1]/v[0] : 0;
	else
		v[3]=CURRENT;
RESULT(v[3])

EQUATION("Government_Investment_GDP_Ratio")
	v[1]=V("Government_Effective_Investment");
	v[2]=V("Country_GDP");
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])

EQUATION("Government_RND_Expenses")
	v[1]=V("Government_Effective_Wages");
	v[2]=V("government_rnd_proportion");
	v[3]= v[1]*v[2];
RESULT(v[3])

EQUATION("Government_Accumulated_Real_Investment")
	v[0]=CURRENT;
	v[1]=V("Government_Effective_Investment");
	v[2]=VS(capital, "Sector_Avg_Price");
	v[3]=v[0]+(v[1]/v[2]);
RESULT(v[3])

EQUATION("Government_Accumulated_RND_Expenses")
RESULT(CURRENT+V("Government_RND_Expenses"))







