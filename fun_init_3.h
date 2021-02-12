//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area
//LOG("\nC***Aut is %f.",v[154]);       //breakpoint example

object *country;
object *external;
object *government;
object *financial;
object *consumption;
object *capital;
object *input;
object *centralbank;

double ROUND( double x , string d = "none")
{
	double r = round(x);
	double y;
	if(d=="UP")
		y = r>x? r: r+1;
	else if(d=="DOWN")
		y = r<x? r: r-1;
	else
		y = r;
	return y;
}

double LAG_SUM( object *obj , const char *var , int lag = 0, int lag2 = 0)
{
	double x = 0;
	int i;
	for(i=lag2+1; i<=lag2+lag; i++)
		x = x + VLS( obj, var, i);
	return x;
}

double LAG_AVE( object *obj , const char *var , int lag = 0, int lag2 = 0)
{
	double x = 0;
	int i;
	for(i=lag2+1; i<=lag2+lag; i++)
		x = x + VLS( obj, var, i);
	return x/lag;
}





MODELBEGIN

EQUATION("Initialization_2")

consumption=SEARCH_CND("id_consumption_goods_sector",1);
capital=SEARCH_CND("id_capital_goods_sector",1);
input=SEARCH_CND("id_intermediate_goods_sector",1);
government=SEARCH("GOVERNMENT");
financial=SEARCH("FINANCIAL");
external=SEARCH("EXTERNAL_SECTOR");
country=SEARCH("COUNTRY");
centralbank=SEARCH("CENTRAL_BANK");

//v[0]=V("depreciation_scale");
v[0]=1;

v[1]=VS(consumption, "sector_number_object_firms");
v[2]=VS(capital, "sector_number_object_firms");
v[3]=VS(input, "sector_number_object_firms");

v[4]=VS(consumption, "sector_investment_frequency");
v[5]=VS(capital, "sector_investment_frequency");
v[6]=VS(input, "sector_investment_frequency");

//v[7]=VS(country, "investment_share_GDP");
//v[8]=VS(country, "exports_share_GDP");
//v[9]=VS(country, "government_share_GDP");
v[7]=0.1;
v[8]=0.1;
v[9]=0.2;

v[10]=VS(consumption, "sector_initial_price");
v[11]=VS(capital, "sector_initial_price");
v[12]=VS(input, "sector_initial_price");

v[13]=VS(consumption, "sector_exports_share");
v[14]=VS(capital, "sector_exports_share");
v[15]=VS(input, "sector_exports_share");

v[16]=VS(government, "government_initial_consumption_share");
v[17]=VS(government, "government_initial_capital_share");
v[18]=VS(government, "government_initial_input_share");

v[19]=v[0]*((v[1]/v[4])+(v[2]/v[5])+(v[3]/v[6]));//domestic real capital demand
	LOG("\nDomestic Capital Demand is %f.",v[19]);
v[20]=(v[11]*v[19])/v[7];//nominal quarterly GDP
	LOG("\nNominal Quarterly GDP is %f.",v[20]);

v[21]=VS(government, "initial_government_debt_share_GDP");
v[22]=VS(country, "annual_frequency");
v[23]=v[20]*v[21]*v[22];//government debt
	LOG("\nGovernment Debt is %f.",v[23]);
v[24]=VS(financial, "real_interest_rate")+VS(centralbank, "target_inflation");
v[25]=v[24]*v[23];//government interest payment
	LOG("\nGovernment Interest Payment is %f.",v[25]);
v[26]=v[9]*v[20];//government total expenses
	LOG("\nGovernment Total Expenses is %f.",v[26]);
v[27]=v[25]+v[26];//government total taxes
	LOG("\nGovernment Total Taxes is %f.",v[27]);
v[28]=v[16]*v[26];//government consumption expenses
	LOG("\nGovernment Nominal Consumption is %f.",v[28]);
v[29]=v[17]*v[26];//government capital expenses
	LOG("\nGovernment Nominal Investment is %f.",v[29]);
v[30]=v[18]*v[26];//government input expenses
	LOG("\nGovernment Nominal Inputs is %f.",v[30]);
v[31]=v[28]/v[10];//government consumption real demand
	LOG("\nGovernment Real Consumption is %f.",v[31]);
v[32]=v[29]/v[11];//government capital real demand
	LOG("\nGovernment Real Capital is %f.",v[32]);
v[33]=v[30]/v[12];//government input real demand
	LOG("\nGovernment Real Inputs is %f.",v[33]);
v[34]=v[26]*(1-v[16]-v[17]-v[18]);//government wages
	LOG("\nGovernment Wages is %f.",v[34]);
	
v[35]=v[20]*v[8];//total exports
	LOG("\nTotal Exports is %f.",v[35]);
//v[36]=VS(external,"initial_trade_balance_share_GDP");
v[36]=0;
v[37]=v[35]-v[36]*v[20];//total imports
	LOG("\nTotal Imports is %f.",v[35]);
v[38]=v[35]*v[13];//nominal consumption exports
	LOG("\nNominal Consumption Exports is %f.",v[38]);
v[39]=v[35]*v[14];//nominal capital exports
	LOG("\nNominal Capital Exports is %f.",v[39]);
v[40]=v[35]*v[15];//nominal input exports
	LOG("\nNominal Input Exports is %f.",v[40]);

v[41]=v[38]/v[10];//real consumption exports
	LOG("\nReal Consumption Exports is %f.",v[41]);
v[42]=v[39]/v[11];//real capital exports
	LOG("\nReal Capital Exports is %f.",v[42]);
v[43]=v[40]/v[12];//real input exports
	LOG("\nReal Input Exports is %f.",v[43]);
	
v[44]=v[42]+v[32]+v[19];//total capital demand
	LOG("\nReal Total Capital Demand is %f.",v[44]);
	WRITES(capital, "sector_initial_demand", v[44]);
v[45]=VS(capital, "sector_desired_degree_capacity_utilization");
v[46]=v[44]/v[2];//capital sector firm demand
	LOG("\nCapital Sector Firm Demand is %f.",v[46]);
v[47]=v[46]/v[45];//capital sector firm productive capacity
	LOG("\nCapital Sector Firm Capacity is %f.",v[47]);
v[48]=VS(capital, "sector_capital_output_ratio");
v[49]=ROUND(v[48]*v[47], "UP");
	LOG("\nCapital Sector Firm Number Capitals is %f.",v[49]);
v[50]=v[46]/v[49];//effective capacity utilization
	LOG("\nCapital Sector Effective Capaicty Utilization is %f.",v[50]);

v[51]=v[20]*(1-v[7]-v[8]-v[9])-v[25];//domestic consumption
	LOG("\nNominal Domestic Consumtpion is %f.",v[51]);
v[52]=v[51]+v[37];//total classes expenses
	LOG("\nTotal Classes Expenses is %f.",v[52]);
	
v[53]=v[51]/v[10];//domestic real consumption
	LOG("\nReal Domestic Consumtpion is %f.",v[53]);
v[54]=v[53]+v[31]+v[41];//consumption sector real demand
	LOG("\nReal Total Consumption Demand is %f.",v[54]);
	WRITES(consumption, "sector_initial_demand", v[54]);
v[55]=VS(consumption, "sector_desired_degree_capacity_utilization");
v[56]=v[54]/v[1];//consumption sector firm demand
	LOG("\nConsumption Sector Firm Demand is %f.",v[56]);
v[57]=v[56]/v[55];//consumption sector firm productive capacity
	LOG("\nConsumpion Sector Firm Capacity is %f.",v[57]);
v[58]=VS(consumption, "sector_capital_output_ratio");
v[59]=ROUND(v[58]*v[57], "UP");
	LOG("\nConsumption Sector Firm Number Capitals is %f.",v[59]);
v[60]=v[56]/v[59];//effective capacity utilization
	LOG("\nConsumption Sector Effective Capaicty Utilization is %f.",v[60]);
	
v[61]=VS(consumption,"sector_input_tech_coefficient");
v[62]=VS(capital,"sector_input_tech_coefficient");
v[63]=VS(input,"sector_input_tech_coefficient");	

v[64]=(v[54]*v[61] + v[44]*v[62] + v[33] + v[43])/(1-v[63]);
	LOG("\nReal Total Input Demand is %f.",v[64]);
	WRITES(input, "sector_initial_demand", v[64]);
v[65]=VS(input, "sector_desired_degree_capacity_utilization");
v[66]=v[64]/v[3];//input sector firm demand
	LOG("\nInput Sector Firm Demand is %f.",v[66]);
v[67]=v[66]/v[65];//input sector firm productive capacity
	LOG("\nInput Sector Firm Capacity is %f.",v[67]);
v[68]=VS(input, "sector_capital_output_ratio");
v[69]=ROUND(v[68]*v[67], "UP");
	LOG("\nInput Sector Firm Number Capitals is %f.",v[69]);
v[70]=v[66]/v[69];//effective capacity utilization
	LOG("\nInput Sector Effective Capaicty Utilization is %f.",v[70]);
	
v[71]=VS(financial, "spread_long_term");
v[72]=VS(financial, "risk_premium_long_term");
v[73]=VS(financial, "spread_deposits");

v[124]=v[125]=v[126]=v[127]=v[128]=v[129]=v[135]=v[139]=v[140]=v[142]=v[144]=0;
CYCLE(cur, "SECTORS")
{
	v[100]=VS(cur, "sector_initial_demand");
	v[101]=VS(cur, "sector_initial_debt_ratio");
	v[102]=VS(cur, "sector_liquidity_preference");
	v[103]=VS(cur, "sector_capital_output_ratio");
	v[104]=VS(cur, "sector_desired_degree_capacity_utilization");
	v[105]=VS(cur, "sector_initial_price");
	v[106]=VS(cur, "sector_initial_productivity");
	v[107]=VS(cur, "sector_indirect_tax_rate");
	v[108]=VS(cur, "sector_rnd_revenue_proportion");
	v[109]=VS(cur, "sector_input_tech_coefficient");
	v[110]=VS(cur, "sector_profit_rate");
	v[111]=VS(cur, "sector_number_object_firms");
	
	v[112]=ROUND((((v[100]/v[111])/v[104])*v[103]),"UP")*v[111]*v[11];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Capital is %f.",v[112]);
	v[113]=v[112]*v[102];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Deposits is %f.",v[113]);
	v[114]=v[112]*(1+v[102])*v[101];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Loans is %f.",v[114]);
	v[115]=(v[24]-v[73])*v[113];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Interest on Deposits is %f.",v[115]);
	v[116]=(v[24]+v[71]+v[72]*v[101])*v[114];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Interest Payment is %f.",v[116]);
	v[117]=v[100]*v[105];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Revenue is %f.",v[117]);
	v[118]=v[100]*v[105]*v[107];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Taxation is %f.",v[118]);
	v[119]=v[100]*v[105]*(1-v[107])*v[108];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("RND Expenses is %f.",v[119]);
	v[120]=v[100]*v[109]*v[12];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Input Expenses is %f.",v[120]);
	v[121]=v[100]*v[110];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Gross Profits is %f.",v[121]);
	v[122]=v[117]-v[118]-v[119]-v[120]-v[116]+v[115]-v[121];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Wage Payment is %f.",v[122]);
	v[123]=(v[122]/v[100])*v[106];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Nominal Wage Rate is %f.",v[123]);
		
	v[124]=v[124]+v[115];//total interest receivment
	v[125]=v[125]+v[116];//total interest payment
	v[126]=v[126]+v[119]+v[122];//total wage payment including RND
	v[127]=v[127]+v[120];//total input expenses
	v[128]=v[128]+v[121];//total profits
	v[129]=v[129]+v[118];//total indirect taxation
	
	v[130]=VS(cur, "sector_investment_frequency");
	v[131]=VS(cur, "sector_amortization_period");
	v[132]=v[0]*v[111]/v[130];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Capital Demand is %f.",v[132]);
	v[133]=v[132]*v[11];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Investment Expenses is %f.",v[133]);
	v[134]=v[114]/v[131];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Amortization Expenses is %f.",v[134]);
	v[135]=v[135]+v[133];
	v[136]=v[133]-v[134];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Retained Profits is %f.",v[136]);
	v[137]=v[121]-v[136];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Distributed Profits is %f.",v[137]);
	v[138]=v[137]/v[121];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Profit Distribution Rate is %f.",v[138]);
	v[139]=v[139]+v[137];
	v[140]=v[140]+v[136];
	v[141]=v[100]/v[106];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Employment is %f.",v[141]);
	v[142]=v[142]+v[141];
	v[143]=v[141]/v[111];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Firm Employment is %f.",v[143]);
	v[144]=v[144]+v[123]*v[141];
	
	
	
}
	LOG("\nTotal Interest Receivment is %f.",v[124]);
	LOG("\nTotal Interest Payment is %f.",v[125]);
	LOG("\nTotal Wages is %f.",v[126]+v[34]);
	LOG("\nTotal Input Expenses is %f.",v[127]+v[30]+v[40]);
	LOG("\nTotal Productive Profits is %f.",v[128]);
	LOG("\nTotal Indirect Taxation is %f.",v[129]);
	LOG("\nFinancial Sector Profits is %f.",v[125]-v[124]+v[25]);
	LOG("\nNominal GDP Income is %f.",v[126]+v[34]+v[128]+v[125]-v[124]+v[25]);
	LOG("\nTotal Investment Expenses is %f.",v[135]+v[29]+v[39]);
	LOG("\nTotal Distributed Profits is %f.",v[139]);
	LOG("\nTotal Retained Profits is %f.",v[140]);
	LOG("\nTotal Sectors Employment is %f.",v[142]);
	LOG("\nAvg Wage Rate is %f.",v[144]/v[142]);
	LOG("\nGovernment Employment is %f.",v[34]/(v[144]/v[142]));
	LOG("\nTotal Labor Force is %f.",v[142]+v[34]/(v[144]/v[142]));
	
//v[160]=VS(country, "unemployment_rate");
v[160]-0;
v[161]=(v[142]+v[34]/(v[144]/v[142]))/(1-v[160]);
	LOG("\nTotal Population is %f.", ROUND(v[161], "UP"));
v[162]=VS(financial, "number_object_banks");
v[163]=SUM("sector_number_object_firms");
v[164]=v[162]+v[163]+ROUND(v[142]+v[34]/(v[144]/v[142]),"UP");

v[150]=v[139]+v[125]-v[124]+v[25]+v[126]+v[34];
	LOG("\nHouseholds Gross Income is %f.",v[150]);
v[151]=v[27]-v[129];
	LOG("\nTotal Income Tax is %f.",v[151]);
v[152]=v[150]-v[151];
	LOG("\nHouseholds Disposable Income is %f.",v[152]);
v[153]=v[52]/v[152];
	LOG("\nHouseholds Propensity to Spend is %f.",v[153]);
	LOG("\nHouseholds Domestic Consumption is %f.",v[51]);
	LOG("\nHouseholds Inported Consumption is %f.",v[37]);
	LOG("\nHouseholds Total Consumption is %f.",v[51]+v[37]);
v[154]=v[151]/v[150];
	LOG("\nHouseholds Tax Rate is %f.",v[154]);
v[155]=v[37]/(v[51]+v[37]);
	LOG("\nHouseholds Imports Rate is %f.",v[155]);
	LOG("\nTotal Consumpion Expenses is %f.",v[51]+v[28]+v[38]);
	
cur1=SEARCH_CND("id_class", 1);
cur2=SEARCH_CND("id_class", 2);
cur3=SEARCH_CND("id_class", 3);
	
CYCLE(cur, "CLASSES")
{
	if(VS(cur,"id_class")==1)
	{
		v[170]=v[125]-v[124]+v[25];
		v[171]=v[162];
	}
	if(VS(cur,"id_class")==2)
	{
		v[170]=v[139];
		v[171]=v[163];
	}
	if(VS(cur,"id_class")==3)
	{
		v[170]=v[126]+v[34];
		v[171]=ROUND(v[142]+v[34]/(v[144]/v[142]),"UP");
	}
	v[172]=v[171]/v[164];
	v[173]=v[170]/v[150];
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Income is %f.",v[170]);
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Population is %f.",v[171]);
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Income Share is %f.",v[173]);
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Population Share is %f.",v[172]);
		WRITES(cur, "class_population_share", v[172]);
		WRITES(cur, "class_income_share", v[173]);
	v[174]=v[154]*v[170];
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Taxation is %f.",v[174]);
	v[175]=(1-v[154])*v[170];
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Disposable Income is %f.",v[175]);
		WRITES(cur, "class_disposable_income", v[175]);
}		
	v[176]=VS(cur3, "class_disposable_income");
	v[177]=0;
		
	v[178]=(1-v[155])*v[153]*VS(cur2, "class_disposable_income");
	v[179]=(v[155])*v[153]*VS(cur2, "class_disposable_income");
		
	v[180]=v[51]-v[176]-v[178];
	v[181]=v[37]-v[177]-v[179];

CYCLE(cur, "CLASSES")
{
	if(VS(cur,"id_class")==3)
	{
		v[182]=v[176];
		v[183]=0;
	}
	if(VS(cur,"id_class")==2)
	{
		v[182]=v[178];
		v[183]=v[179];
	}
	if(VS(cur,"id_class")==1)
	{
		v[182]=v[180];
		v[183]=v[181];
	}
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Domestic Consumption is %f.",v[182]);
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Imported Consumption is %f.",v[183]);
	v[184]=v[183]/(v[182]+v[183]);
		LOG("\nClass %.0f ",VS(cur,"id_class")); LOG("Imported Share is %f.",v[184]);
	v[185]=(v[182]+v[183])/VS(cur, "class_disposable_income");
		LOG("\nClass %f ",VS(cur,"id_class")); LOG("Propensity to Spend is %f.",v[185]);

}	

v[191]=VS(cur1, "class_income_share");
v[192]=VS(cur2, "class_income_share");
v[193]=VS(cur3, "class_income_share");
v[194]=VS(cur1, "class_population_share");
v[195]=VS(cur2, "class_population_share");
v[196]=VS(cur3, "class_population_share");
v[197]=1-v[191]*v[194]-v[192]*v[195]-v[193]*v[196]-2*v[193]*v[195]-2*v[193]*v[194]-2*v[192]*v[194];
LOG("Gini Index is %f.",v[197]);


	
	

PARAMETER
RESULT(0)













/*




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
  WRITELLS(cur, "Sector_Productive_Capacity", SUMS(cur, "Firm_Productive_Capacity"),0,1);
  WRITES(cur, "sector_desired_degree_capacity_utilization", AVES(cur, "Firm_Capacity_Utilization"));	                    						 												
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

//COUNTRY VARIABLES

EQUATION("Country_Annual_Growth")
RESULT(CURRENT)

EQUATION("Country_Annual_Real_Growth")
RESULT(CURRENT)

EQUATION("Country_Annual_Inflation")
RESULT(CURRENT)

EQUATION("Country_Price_Index")
RESULT(CURRENT)

EQUATION("Country_Consumer_Price_Index")
RESULT(CURRENT)

EQUATION("Country_Capital_Goods_Price")
RESULT(CURRENT)

EQUATION("Country_Avg_Productivity")
RESULT(CURRENT)

EQUATION("Country_GDP")
RESULT(CURRENT)

EQUATION("Country_Real_GDP")
RESULT(CURRENT)

//EXTERNAL SECTOR VARIABLES

EQUATION("Capital_Flows")
RESULT(CURRENT)

EQUATION("Trade_Balance")
RESULT(CURRENT)

EQUATION("External_Income")
RESULT(CURRENT)

EQUATION("International_Reserves")
RESULT(CURRENT)

//GOVERNMENT VARIABLES

EQUATION("Government_Total_Taxes")
RESULT(CURRENT)

EQUATION("Government_Max_Expenses")
RESULT(CURRENT)

EQUATION("Government_Desired_Wages")
RESULT(CURRENT)

EQUATION("Government_Desired_Consumption")
RESULT(CURRENT)

EQUATION("Government_Desired_Investment")
RESULT(CURRENT)

EQUATION("Government_Desired_Inputs")
RESULT(CURRENT)

EQUATION("Government_Surplus_Rate_Target")
RESULT(CURRENT)

EQUATION("Government_Effective_Wages")
RESULT(CURRENT)

EQUATION("Government_Debt")
RESULT(CURRENT)

EQUATION("Government_Debt_GDP_Ratio")
RESULT(CURRENT)

EQUATION("Government_Effective_Expenses")
RESULT(CURRENT)

//CLASS VARIABLES

EQUATION("Class_Nominal_Disposable_Income")
RESULT(CURRENT)

EQUATION("Class_Real_Disposable_Income")
RESULT(CURRENT)

EQUATION("Class_Avg_Nominal_Income")
RESULT(CURRENT)

EQUATION("Class_Avg_Real_Income")
RESULT(CURRENT)

EQUATION("Class_Real_Autonomous_Consumption")
RESULT(CURRENT)

EQUATION("Class_Liquidity_Preference")
RESULT(CURRENT)

EQUATION("Class_Desired_Debt_Rate")
RESULT(CURRENT)

EQUATION("Class_Debt_Rate")
RESULT(CURRENT)

EQUATION("Class_Stock_Deposits")
RESULT(CURRENT)

//SECTOR VARIABLES

EQUATION("Sector_Demand_Met")
RESULT(CURRENT)

EQUATION("Sector_Demand_Met_By_Imports")
RESULT(CURRENT)

EQUATION("Sector_Effective_Orders")
RESULT(CURRENT)

EQUATION("Sector_Productive_Capacity_Available")
RESULT(CURRENT)

EQUATION("Sector_Avg_Competitiveness")
RESULT(CURRENT)

EQUATION("Sector_External_Price")
RESULT(CURRENT)

EQUATION("Sector_Avg_Productivity")
RESULT(CURRENT)

EQUATION("Sector_Max_Productivity")
RESULT(CURRENT)

EQUATION("Sector_Max_Quality")
RESULT(CURRENT)

EQUATION("Sector_Inventories")
RESULT(CURRENT)

EQUATION("Sector_Real_Exports")
RESULT(CURRENT)

EQUATION("Sector_Avg_Quality")
RESULT(CURRENT)

EQUATION("Sector_Employment")
RESULT(CURRENT)

EQUATION("Sector_Avg_Price")
RESULT(CURRENT)

EQUATION("Sector_Productive_Capacity")
RESULT(CURRENT)

//FINANCIAL SECTOR VARIABLES

EQUATION("Basic_Interest_Rate")
RESULT(CURRENT)

EQUATION("Avg_Competitiveness_Financial_Sector")
RESULT(CURRENT)

EQUATION("Avg_Interest_Rate_Long_Term")
RESULT(CURRENT)

EQUATION("Avg_Interest_Rate_Short_Term")
RESULT(CURRENT)

//BANK VARIABLES

EQUATION("Bank_Market_Share")
RESULT(CURRENT)

EQUATION("Bank_Competitiveness")
RESULT(CURRENT)

EQUATION("Bank_Accumulated_Profits")
RESULT(CURRENT)

EQUATION("Bank_Demand_Met")
RESULT(CURRENT)

EQUATION("Bank_Desired_Long_Term_Spread")
RESULT(CURRENT)

EQUATION("Bank_Desired_Short_Term_Spread")
RESULT(CURRENT)

EQUATION("Bank_Interest_Rate_Short_Term")
RESULT(CURRENT)

EQUATION("Bank_Interest_Rate_Long_Term")
RESULT(CURRENT)

//FIRM VARIABLES

EQUATION("Firm_Demand_Productive_Capacity_Replacement")
RESULT(CURRENT)

EQUATION("Firm_Debt_Rate")
RESULT(CURRENT)

EQUATION("Firm_Demand_Capital_Goods")
RESULT(CURRENT)

EQUATION("Firm_Frontier_Productivity")
RESULT(CURRENT)

EQUATION("Firm_Max_Productivity")
RESULT(CURRENT)

EQUATION("Firm_Avg_Productivity")
RESULT(CURRENT)

EQUATION("Firm_Capacity_Utilization")
RESULT(CURRENT)

EQUATION("Firm_Productive_Capacity_Depreciation")
RESULT(CURRENT)

EQUATION("Firm_Demand_Productive_Capacity_Expansion")
RESULT(CURRENT)

EQUATION("Firm_Demand_Capital_Goods_Expansion")
RESULT(CURRENT)

EQUATION("Firm_Demand_Capital_Goods_Replacement")
RESULT(CURRENT)

EQUATION("Firm_Effective_Orders_Capital_Goods")
RESULT(CURRENT)

EQUATION("Firm_Effective_Orders")
RESULT(CURRENT)

EQUATION("Firm_Market_Share")
RESULT(CURRENT)

EQUATION("Firm_Potential_Markup")
RESULT(CURRENT)

EQUATION("Firm_Effective_Market_Share")
RESULT(CURRENT)



EQUATION("Firm_Desired_Market_Share")
RESULT(CURRENT)

EQUATION("Firm_Avg_Market_Share")
RESULT(CURRENT)

EQUATION("Firm_Price")
RESULT(CURRENT)

EQUATION("Firm_Sales")
RESULT(CURRENT)

EQUATION("Firm_Revenue")
RESULT(CURRENT)

EQUATION("Firm_Stock_Inventories")
RESULT(CURRENT)

EQUATION("Firm_Stock_Inputs")
RESULT(CURRENT)

EQUATION("Firm_Productive_Capacity")
RESULT(CURRENT)

EQUATION("Firm_Capital")
RESULT(CURRENT)

EQUATION("Firm_Wage")
RESULT(CURRENT)

EQUATION("Firm_Variable_Cost")
RESULT(CURRENT)

EQUATION("Firm_Avg_Potential_Markup")
RESULT(CURRENT)

EQUATION("Firm_Desired_Markup")
RESULT(CURRENT)

EQUATION("Firm_Competitiveness")
RESULT(CURRENT)

EQUATION("Firm_Potential_Markup")
RESULT(CURRENT)

EQUATION("Firm_Delivery_Delay")
RESULT(CURRENT)

EQUATION("Firm_Stock_Deposits")
RESULT(CURRENT)

EQUATION("Firm_Stock_Loans")
RESULT(CURRENT)

EQUATION("Firm_Avg_Debt_Rate")
RESULT(CURRENT)

EQUATION("Firm_Desired_Debt_Rate")
RESULT(CURRENT)

EQUATION("Firm_Liquidity_Preference")
RESULT(CURRENT)  

//CAPITAL VARIABLES

EQUATION("Capital_Good_Acumulated_Production")
RESULT(CURRENT) 

EQUATION("Total_Depreciation")
v[0]=0;
CYCLE(cur,"SECTORS")
{
	CYCLES(cur, cur1, "FIRMS")
	{
		CYCLES(cur1, cur2, "CAPITALS")
		{	
			if(t==VS(cur2, "capital_good_depreciation_period"))
			v[0]=v[0]+1;
		}
	}
}
RESULT(v[0])

*/

MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
