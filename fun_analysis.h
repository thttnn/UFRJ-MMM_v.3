/***********ANALYSIS VARIABLES************/

/*****COUNTRY STATS*****/

EQUATION("GDP")//Nominal GDP
RESULT(VS(country, "Country_GDP_Demand"))

EQUATION("P")//Price Index
RESULT(VS(country, "Country_Price_Index"))

EQUATION("CPI")//Price Index
RESULT(VS(country, "Country_Consumer_Price_Index"))

EQUATION("P_G")//Inflation
RESULT(VS(country, "Country_Annual_Inflation"))

EQUATION("CPI_G")//Inflation
RESULT(VS(country, "Country_Annual_CPI_Inflation"))

EQUATION("U")//Unemployment
RESULT(VS(country, "Country_Idle_Capacity"))

EQUATION("EMP")//Employment
RESULT(SUMS(country, "Sector_Employment"))

EQUATION("GDP_G")//GDP real growth rate
RESULT(VS(country, "Country_Annual_Real_Growth"))

EQUATION("G_n")//GDP nominal growth rate
RESULT(VS(country, "Country_Annual_Growth"))

EQUATION("Cri")//Crisis counters
RESULT(VS(country, "Country_Likelihood_Crisis"))

EQUATION("C")//Quarterly Nominal Consumption
RESULT(VS(country, "Country_Nominal_Consumption_Production"))

EQUATION("I")//Quarterly Nominal Investment
RESULT(VS(country, "Country_Nominal_Capital_Production"))

EQUATION("PROD")//Average Productivity
RESULT(VS(country, "Country_Avg_Productivity"))

EQUATION("MK")//Average Markup
RESULT(VS(country, "Country_Avg_Markup"))

EQUATION("PDEBT")//Public Debt
RESULT(VS(government, "Government_Debt"))

EQUATION("KL")//Capital labour ratio
RESULT(VS(country,"Country_Capital_Labor_Ratio"))

EQUATION("PR")//Profit Rate
RESULT(VS(country,"Country_Avg_Profit_Rate"))

EQUATION("PCU")//Productive Capacity Utilization Rate
RESULT(VS(country,"Country_Capacity_Utilization"))

EQUATION("PSH")//Profit Share
RESULT(VS(country,"Country_Profit_Share"))

EQUATION("WSH")//Wage Share
RESULT(VS(country,"Country_Wage_Share"))


/*****REAL STATS*****/

EQUATION("GDP_r")//Real GDP
RESULT(VS(country, "Country_Real_GDP_Demand"))

EQUATION("C_r")//Quarterly Real Consumption
RESULT(VS(country, "Country_Nominal_Consumption_Production")/V("P"))

EQUATION("I_r")//Quarterly Real Investment
RESULT(VS(country, "Country_Nominal_Capital_Production")/V("P"))

EQUATION("INVE_r")//Real Aggregate Inventories
RESULT(VS(country, "Country_Inventories")/V("P"))

EQUATION("K_r")//Real Stock of Capital
RESULT(VS(country, "Country_Capital_Stock")/V("P"))

EQUATION("G_r")//Quarterly Real Government Expenses
RESULT(VS(government, "Government_Effective_Expenses")/V("P"))

EQUATION("PROFITS")//Real Profits
RESULT(VS(country, "Country_Total_Profits")/V("P"))

EQUATION("WAGE")//Real Wages
RESULT(VS(country, "Country_Total_Wages")/V("P"))

EQUATION("M_r")//Quarterly Real Imports
RESULT(VS(country, "Country_Nominal_Imports")/V("P"))

EQUATION("X_r")//Quarterly Real Exports
RESULT(VS(country, "Country_Nominal_Exports")/V("P"))

EQUATION("NX_r")//Quarterly Real Net Exports
RESULT(V("X_r")-V("M_r"))


/*****FINANCIAL STATS*****/

EQUATION("DEBT_RT_C")//Average Debt Rate of Consumption good sector
RESULT(VS(consumption, "Sector_Avg_Debt_Rate"))

EQUATION("DEBT_RT_K")//Average Debt Rate of Capital good sector
RESULT(VS(capital, "Sector_Avg_Debt_Rate"))

EQUATION("DEBT_RT_I")//Average Debt Rate of Intermediate good sector
RESULT(VS(input, "Sector_Avg_Debt_Rate"))

EQUATION("DEBT_RT_FI")//Average Debt Rate of all firms
RESULT(VS(country, "Country_Debt_Rate_Firms"))

EQUATION("DEBT_RT_CL")//Average Debt Rate of all classes
RESULT(VS(country, "Country_Debt_Rate_Class"))

EQUATION("DEBT_FS_ST")//Stock of short term debt in the financial sector
RESULT(VS(financial, "Financial_Sector_Stock_Loans_Short_Term"))

EQUATION("DEBT_FS_LT")//Stock of long term debt in the financial sector
RESULT(VS(financial, "Financial_Sector_Stock_Loans_Long_Term"))

EQUATION("DEBT_FS")//Stock of total debt in the financial sector
RESULT(VS(financial, "Financial_Sector_Total_Stock_Loans"))

EQUATION("DEP_FS")//Stock of total deposits in the financial sector
RESULT(VS(financial, "Financial_Sector_Stock_Deposits"))

EQUATION("FS_STR")//Financial sector short term rate
RESULT(VS(financial, "Financial_Sector_Short_Term_Rate"))

EQUATION("FS_LEV")//Financial sector leverage
RESULT(VS(financial, "Financial_Sector_Leverage"))

EQUATION("FS_HHI")//Financial sector HHI
RESULT(VS(financial, "Financial_Sector_Normalized_HHI"))

EQUATION("FS_DR")//Financial sector Default rate
RESULT(VS(financial, "Financial_Sector_Default_Rate"))

EQUATION("FS_DEF")//Financial sector Default
RESULT(VS(financial, "Financial_Sector_Defaulted_Loans"))
   
EQUATION("FS_PR")//Financial sector profits
RESULT(VS(financial, "Financial_Sector_Profits"))   

EQUATION("PONZI")//Share of Firms in Ponzi position
RESULT(VS(country, "Country_Ponzi_Share"))    

EQUATION("SPEC")//Share of Firms in Speculative position
RESULT(VS(country, "Country_Speculative_Share"))  

EQUATION("HEDGE")//Share of Firms in Hedge position
RESULT(VS(country, "Country_Hedge_Share")) 

EQUATION("IR")//Basic Interest Rate
RESULT(VS(financial, "Central_Bank_Basic_Interest_Rate"))     

EQUATION("IR_DEP")//Interest Rate on Deposits
RESULT(VS(financial, "Financial_Sector_Interest_Rate_Deposits"))  

EQUATION("IR_ST")//Interest Rate on Short Term Loans
RESULT(VS(financial, "Financial_Sector_Avg_Interest_Rate_Short_Term"))  

EQUATION("IR_LT")//Interest Rate on Long Term Loans
RESULT(VS(financial, "Financial_Sector_Avg_Interest_Rate_Long_Term"))   

EQUATION("BKR")//Number of Bankrupt Events
RESULT(VS(country, "Exit_Bankruptcy_Events")) 

EQUATION("BKR_RT")//Bankrupt Rate
RESULT(VS(country, "Exit_Bankruptcy_Share")) 

/*****CLASS STATS*****/
EQUATION("YSH_A")
cur=SEARCH_CNDS(country, "class_id", 1);
RESULT(VS(cur, "Class_Income_Share"))

EQUATION("YSH_B")
cur=SEARCH_CNDS(country, "class_id", 2);
RESULT(VS(cur, "Class_Income_Share"))

EQUATION("YSH_C")
cur=SEARCH_CNDS(country, "class_id", 3);
RESULT(VS(cur, "Class_Income_Share"))

EQUATION("WSH_A")
cur=SEARCH_CNDS(country, "class_id", 1);
RESULT(VS(cur, "Class_Wealth_Share"))

EQUATION("WSH_B")
cur=SEARCH_CNDS(country, "class_id", 2);
RESULT(VS(cur, "Class_Wealth_Share"))

EQUATION("WSH_C")
cur=SEARCH_CNDS(country, "class_id", 3);
RESULT(VS(cur, "Class_Wealth_Share"))


/*****SECTORAL STATS*****/

EQUATION("P_C")//Average Price of Consumption good secto
RESULT(VS(consumption, "Sector_Avg_Price"))

EQUATION("P_K")//Average Price of Capital good sector
RESULT(VS(capital, "Sector_Avg_Price"))

EQUATION("P_I")//Average Price of Intermediate good sector
RESULT(VS(input, "Sector_Avg_Price"))

EQUATION("W_C")//Average Wage of Consumption good sector
RESULT(VS(consumption, "Sector_Avg_Wage"))

EQUATION("W_K")//Average Wage of Capital good sector
RESULT(VS(capital, "Sector_Avg_Wage"))

EQUATION("W_I")//Average Wage of Intermediate good sector
RESULT(VS(input, "Sector_Avg_Wage"))

EQUATION("MK_C")//Average Markup of Consumption good sector
RESULT(VS(consumption, "Sector_Avg_Markup"))

EQUATION("MK_K")//Average Markup of Capital good sector
RESULT(VS(capital, "Sector_Avg_Markup"))

EQUATION("MK_I")//Average Markup of Intermediate good sector
RESULT(VS(input, "Sector_Avg_Markup"))

EQUATION("PROD_C")//Average Productivity of Consumption good sector
RESULT(VS(consumption, "Sector_Avg_Productivity"))

EQUATION("PROD_K")//Average Productivity of Capital good sector
RESULT(VS(capital, "Sector_Avg_Productivity"))

EQUATION("PROD_I")//Average Productivity of Intermediate good sector
RESULT(VS(input, "Sector_Avg_Productivity"))

EQUATION("U_C")//Unemployment Rate of Consumption good sector
RESULT(VS(consumption, "Sector_Idle_Capacity"))

EQUATION("U_K")//Unemployment Rate of Capital good sector
RESULT(VS(capital, "Sector_Idle_Capacity"))

EQUATION("U_I")//Unemployment Rate of Intermediate good sector
RESULT(VS(input, "Sector_Idle_Capacity"))

EQUATION("HHI_C")//Inverse HHI of Consumption good sector
RESULT(VS(consumption, "Sector_Normalized_HHI"))

EQUATION("HHI_K")//Inverse HHI of Capital good sector
RESULT(VS(capital, "Sector_Normalized_HHI"))

EQUATION("HHI_I")//Inverse HHI of Intermediate good sector
RESULT(VS(input, "Sector_Normalized_HHI"))


/*****COUNTRY GROWTH STATS*****/

EQUATION("EMP_G")
/*
Quarterly Employment Growth rate
*/
v[0]=V("EMP");
v[1]=VL("EMP", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("CON_G")
/*
Quarterly Real Consumption Growth rate
*/
v[0]=V("C_r");
v[1]=VL("C_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("INV_G")
/*
Quarterly Real Investment Growth rate
*/
v[0]=V("I_r");
v[1]=VL("I_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("PROD_G")
/*
Average Productivity Growth
*/
v[0]=V("PROD");
v[1]=VL("PROD", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("MK_G")
/*
Average Markup Growth
*/
v[0]=V("MK");
v[1]=VL("MK", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("INVE_G")
/*
Real Aggregate Inventories Growth
*/
v[0]=V("INVE_r");
v[1]=VL("INVE_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("K_G")
/*
Real Stock of Capital Growth
*/
v[0]=V("K_r");
v[1]=VL("K_r", 1);
if (v[1]!=0)
v[2]=(v[0]-v[1])/v[1];
else
v[2]=0;
RESULT(v[2])

EQUATION("PROFITS_G")
/*
Real Profits Growth rate
*/
v[0]=V("PROFITS");
v[1]=VL("PROFITS", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("WAGE_G")
/*
Real Wages growth rate
*/
v[0]=V("WAGE");
v[1]=VL("WAGE", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("GOV_G")
/*
Quarterly Real Government Expenses Growth rate
*/
v[0]=V("G_r");
v[1]=VL("G_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("PDEBT_G")
/*
Public Debt Growth rate
*/
v[0]=V("PDEBT");
v[1]=VL("PDEBT", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("M_G")
/*
Quarterly Real Imports Growth rate
*/
v[0]=V("M_r");
v[1]=VL("M_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("X_G")
/*
Quarterly Real Exports Growth rate
*/
v[0]=V("X_r");
v[1]=VL("X_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("NX_G")
/*
Quarterly Real Net Exports Growth rate
*/
v[0]=V("NX_r");
v[1]=VL("NX_r", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])


/*****MACRO SHARE STATS*****/


EQUATION("CGDP")
/*
Real Consumption share of GDP
*/
v[0]=V("C_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("IGDP")
/*
Real Investment share of GDP
*/
v[0]=V("I_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("GGDP")
/*
Real Government Expenses share of GDP
*/
v[0]=V("G_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("NXGDP")
/*
Real net exports share of GDP
*/
v[0]=V("NX_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("INVGDP")
/*
Real inventories share of GDP
*/
v[0]=V("INVE_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("KGDP")
/*
Real stock of capital share of GDP, or capital-output ratio
*/
v[0]=V("K_r");
v[1]=VS(country,"Country_Real_GDP");
if(v[1]!=0)
	v[2]=v[0]/v[1];
else
	v[2]=0;
RESULT(v[2]) 


/*****FINANCIAL GROWTH STATS*****/

EQUATION("DEBT_FS_ST_G")
/*
Stock of short term debt growth in the financial sector
*/
v[0]=V("DEBT_FS_ST");
v[1]=VL("DEBT_FS_ST", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("DEBT_FS_LT_G")
/*
Stock of long term debt growth in the financial sector
*/
v[0]=V("DEBT_FS_LT");
v[1]=VL("DEBT_FS_LT", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("DEBT_FS_G")
/*
Stock of total debt growth in the financial sector
*/
v[0]=V("DEBT_FS");
v[1]=VL("DEBT_FS", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])

EQUATION("DEP_FS_G")
/*
Stock of total deposits growth in the financial sector
*/
v[0]=V("DEP_FS");
v[1]=VL("DEP_FS", 1);
if (v[1]!=0)
	v[2]=(v[0]-v[1])/v[1];
else
	v[2]=0;
RESULT(v[2])




