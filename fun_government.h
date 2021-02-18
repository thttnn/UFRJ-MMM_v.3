/*****PUBLIC SECTOR*****/

EQUATION("Government_Desired_Wages")
/*
Priority expenses.
If there are no maximum expenses, it is adjusted by average productivity growth and inflation.
*/

v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust government wages)
{
	v[3]=VLS(consumption, "Sector_Avg_Price",1);                         
	v[4]=VLS(consumption, "Sector_Avg_Price", v[0]+1);       
	v[5]= v[4]!=0? (v[3]-v[4])/v[4] : 0;
	v[6]=V("government_inflation_passtrought");			   		//inflation passtrough to public wages
	v[7]=V("government_real_growth");
	v[8]=v[2]*(1+v[6]*v[5]+v[7]);                 				//desired adjusted government wages with no restriction
}
else                                                          	 //if it is not adjustment period
	v[8]=v[2];                                                	//use last period's
RESULT(max(0,v[8]))


EQUATION("Government_Desired_Unemployment_Benefits")
/*
Counter-cyclical Expenses
Benefit is a share of average wage. 
The amount depends on current unemployment.
*/
v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[2]=V("government_benefit");
	v[3]=0;
	CYCLES(country, cur, "SECTORS")
	{
		v[4]=VS(cur, "sector_desired_degree_capacity_utilization");
		v[5]=VLS(cur, "Sector_Idle_Capacity", 1);
		v[6]=v[5]-(1-v[4]);
		v[7]=VLS(cur, "Sector_Productive_Capacity", 1);
		v[8]=v[6]*v[7];
		v[9]=VLS(cur, "Sector_Avg_Productivity", 1);
		v[10]=VLS(cur, "Sector_Avg_Wage", 1);
		v[11]=v[8]*(v[2]*v[10]/v[9]);
		v[3]=v[3]+v[11];
	}
}
else
	v[3]=CURRENT;
RESULT(max(0,v[3]))


EQUATION("Government_Desired_Investment")
/*
Desired Investment Expenses
Adjusted by a desired real growth rate and avg capital price growth
*/
v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(capital, "Sector_Avg_Price",1);                         
	v[6]=VLS(capital, "Sector_Avg_Price", v[0]+1);                  		
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(max(0,v[8]))


EQUATION("Government_Desired_Consumption")
/*
Desired Consumption Expenses
Adjusted by a desired real growth rate and avg consumption price growth
*/
v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(consumption, "Sector_Avg_Price",1);                         
	v[6]=VLS(consumption, "Sector_Avg_Price", v[0]+1);       
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(max(0,v[8]))


EQUATION("Government_Desired_Inputs")
/*
Desired Intermediate Expenses
Adjusted by a desired real growth rate and avg input price growth
*/
v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(input, "Sector_Avg_Price",1);                         
	v[6]=VLS(input, "Sector_Avg_Price", v[0]+1);       
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(max(0,v[8]))


EQUATION("Government_Surplus_Rate_Target")
/*
Adjusts government surplus target based on debt to gdp evolution
*/
v[0]=V("annual_frequency");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;                   							   //last period's target
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=VL("Government_Debt_GDP_Ratio",1);                    //current debt to gdp ratio
	v[8]=VL("Government_Debt_GDP_Ratio",v[0]+1);
	v[4]=V("government_max_debt");                             //maximum debt to gdp accepted, parameter
	v[5]=V("government_min_debt");                             //minimum debt to gdp accepted, parameter
	v[6]=V("government_surplus_target_adjustment");			   //adjustment parameter
	if(v[3]>v[4]&&v[3]>v[8])                                   //if debt to gdp is higher than accepted and growing
		v[7]=v[2]+v[6];										   //increase surplus target
	else if (v[3]<v[5]&&v[3]<v[8])                             //if debt to gdp is lower than accepted and decreasing
		v[7]=v[2]-v[6];										   //deacrease surplus target
	else                                                       //if current debt to gdp is between accepted band
		v[7]=v[2];                                             //do not change surplus taget
}
else                                                           //if it is not adjustment period
	v[7]=v[2];                                                 //do not change surplus taget
RESULT(v[7])



EQUATION("Government_Max_Expenses_DEBT")
/*
Government Max Expenses determined by Debt Rate Target Fiscal rule
*/
	v[0]=V("government_expectations");
	v[1]=VL("Country_GDP",1);
	v[2]=VL("Country_GDP",2);
	v[3]=VL("Country_GDP",3);
	v[4]= v[2]!=0? v[0]*(v[1]-v[2])/v[2] : 0;
	
	v[5]=V("government_max_debt");
	v[6]=VL("Government_Debt",1);
	v[7]=VL("Government_Total_Taxes",1);
	v[8]=VS(financial, "Basic_Interest_Rate");
	
	v[9]=v[5]*(v[1]*(2+v[4])+v[2]+v[3]) - v[6]*(1+v[8]) + v[7]*(1+v[4]);
RESULT(v[9])
	
EQUATION("Government_Max_Expenses_DEBT_2")
/*
Government Max Expenses determined by Debt Rate Target Fiscal rule
*/
	v[0]=V("government_expectations");
	v[1]=VL("Country_GDP",1);
	v[2]=VL("Country_GDP",2);
	v[3]= v[2]!=0? v[0]*(v[1]-v[2])/v[2] : 0; //expected growth
	
	v[5]=V("government_max_debt");
	v[6]=VL("Government_Debt",1);
	v[7]=VL("Government_Total_Taxes",1);
	v[8]=VS(financial, "Basic_Interest_Rate");
	v[9]=V("annual_frequency");
	
	v[10]=0;
	for(i=1;i<=v[9];i++)
		v[10]=v[10]+pow((1+v[3]),i);//beta
	
	v[11]=1;
	for(i=1;i<=v[9]-1;i++)
		v[11]=v[11]+pow((1+v[8]),i);//alpha
	
	v[12]=0;
	for(i=1,j=v[9]-1;i<=v[9],j>=0;i++,j--)
		v[12]=v[12]+(pow((1+v[3]),i))*(pow((1+v[8]),j));//gamma
	
	if(v[11]!=0)
		v[13]=(v[5]*v[1]*v[10] + v[7]*v[12] - v[6]*pow((1+v[8]),v[9]))/v[11];
	else
		v[13]=0;
	
	v[14]= fmod((double) t,v[9]);                                   //divides the time period by government adjustment period (adjust annualy)
	if(v[14]==0)
		v[15]=v[13];
	else
		v[15]=CURRENT;
RESULT(v[15])

EQUATION("Government_Max_Expenses_Surplus")
/*
Government Max Expenses determined by Primary Surplus Target Fiscal rule
*/
	v[0]=VL("Country_GDP",1);
	v[1]=VL("Country_GDP",2);
	v[2]=V("government_expectations");
	v[3]= v[1]!=0? v[2]*(v[0]-v[1])/v[1] : 0;
	v[4]=V("annual_frequency");
	v[5]=0;
	for(i=1;i<=v[4];i++)
		v[5]=v[5]+pow((1+v[3]),i);
	v[6]=v[5]/v[4];
	v[7]=VL("Government_Total_Taxes",1);
	v[8]=V("Government_Surplus_Rate_Target");
	v[9]=v[6]*(v[7]-v[8]*v[0]);
	v[10]=fmod((double) t,v[4]);
	if(v[10]==0)
		v[11]=v[9];
	else	
		v[11]=CURRENT;
RESULT(v[11])

EQUATION("Government_Max_Expenses_Ceiling")
/*
Government Max Expenses determined by Expenses Ceiling Target Fiscal rule
*/
	v[0]=V("annual_frequency");
	v[1]=VL("Country_Annual_CPI_Inflation",1);
	v[2]=0;
	for(i=1;i<=v[0];i++)
		v[2]=v[2]+VL("Government_Effective_Expenses",i);
	v[3]=v[2]*(1+v[1])/v[0];
	v[4]=fmod((double) t,v[0]);
	if(v[4]==0)
		v[5]=v[3];
	else
		v[5]=CURRENT;
RESULT(v[5])


EQUATION("Government_Max_Expenses")
/*
Maximum Government expenses imposed by the fiscal rule.
Fiscal rules can be two types: primary surplus target or expenses ceiling (or both).
Depend on the policy parameter.
*/
v[0]=V("begin_surplus_target_rule");                           //define when surplus target rule begins
v[1]=V("begin_expenses_ceiling_rule");                         //define when expenses ceiling begins
v[2]=V("annual_frequency");
v[3]= fmod((double) t,v[2]);                                   //divides the time period by government adjustment period (adjust annualy)
if(v[3]==0)                                                    //if the rest of the division is zero (adjust maximum expenses)
{                                                              //adjust fiscal rules maximum expenses
		v[4]=VL("Country_GDP", 1);                                      //GDP lagged 1
		v[5]=VL("Country_GDP", v[2]+1);                                   //GDP lagged government period (4)
		v[6]=V("government_expectations");                              //government expectation parameter 
		if(v[5]!=0)                                                   	//if last semiannual GDP is not zero
			v[7]=1+v[6]*(v[4]-v[5])/v[5];                               //expected growth of gdp
		else                                                          	//if last semiannual GDP is zero
			v[7]=1;                                                     //use one for the expected growth
		v[8]=VL("Government_Total_Taxes",1);                            //total taxes in the last period
		v[9]=V("Government_Surplus_Rate_Target");                     	//government surplus target rate
		v[10]=v[7]*v[8]-(v[7]*v[4]*v[9]);                               //maximum expenses will be total taxes multiplyed by expected growth minus the surplus target
	
		v[11]=VL("Government_Effective_Expenses", 1);                   //last period government expeneses
		v[12]=VL("Country_Consumer_Price_Index",1);                     //consumer price index lagged 1
		v[13]=VL("Country_Consumer_Price_Index", v[2]+1);                 //consumer price index lagged government period (4)
		if(v[13]!=0)                                                    //if consumer price index is not zero
			v[14]=1+((v[12]-v[13])/v[13]);                              //calculate inflation
		else                                                            //if consumer price index is zero
			v[14]=1;												    //use 1
		v[15]=v[11]*v[14];												//maximum expenses if ceiling rule is active
	
	if((t>=v[0]&&v[0]!=-1)&&(t>=v[1]&&v[1]!=-1))                        //if both rules are active
		v[16]=min(v[10],v[15]);                                         //effective maximum is the minimum between both rules
	else if ((t>=v[0]&&v[0]!=-1)&&(t<v[1]||v[1]==-1))                   //if only surplus target is active
		v[16]=v[10];
	else if ((t>=v[1]&&v[1]!=-1)&&(t<v[0]||v[0]==-1))                   //if only expenses ceiling is active
		v[16]=v[15];
	else													            //if none of the rules are active
		v[16]=-1; 											            //no maximum expenses
}
else	                                                                //if it is not adjustment period
	v[16]=CURRENT;											            //use last period's maximum
	
	v[20]=V("Government_Max_Expenses_Surplus");
	v[21]=V("Government_Max_Expenses_Ceiling");
	v[23]=V("begin_debt_target_rule"); 
	v[24]=V("Government_Max_Expenses_DEBT_2");
	
	if((t>=v[0]&&v[0]!=-1)&&(t>=v[1]&&v[1]!=-1)&&(t>=v[23]&&v[23]!=-1))
		v[17]=min(min(v[20],v[21]),v[24]);//three rules
	else if ((t<v[0]||v[0]==-1)&&(t>=v[1]&&v[1]!=-1)&&(t>=v[23]&&v[23]!=-1))
		v[17]=min(v[21],v[24]);//debt rule and celing rule
	else if ((t>=v[0]&&v[0]!=-1)&&(t<v[1]||v[1]==-1)&&(t>=v[23]&&v[23]!=-1))
		v[17]=min(v[20],v[24]);//debt rule and surplus rule
	else if ((t>=v[0]&&v[0]!=-1)&&(t>=v[1]&&v[1]!=-1)&&(t<v[23]||v[23]==-1))
		v[17]=min(v[20],v[21]);//surplus rule and ceiling rule
	else if ((t>=v[0]&&v[0]!=-1)&&(t<v[1]||v[1]==-1)&&(t<v[23]||v[23]==-1))
		v[17]=v[20];//only surplus rule
	else if ((t<v[0]||v[0]==-1)&&(t>=v[1]&&v[1]!=-1)&&(t<v[23]||v[23]==1))
		v[17]=v[21];//only ceiling rule
	else if ((t<v[0]||v[0]==-1)&&(t<v[1]||v[1]==-1)&&(t>=v[23]&&v[23]!=-1))
		v[17]=v[24];//only debt rule
	else
		v[17]=-1;//no rule
	
RESULT(v[17])


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
v[4]=V("Government_Desired_Investment");
v[5]=V("Government_Desired_Inputs");

v[14]=V("government_initial_consumption_share");
v[15]=V("government_initial_capital_share");
v[16]=V("government_initial_input_share");
v[17]=v[14]+v[15]+v[16];

if(v[0]==-1)                                               //no fiscal rule
{
	v[8]=v[1];											   //government wages equal desired wages
	v[9]=v[2];    										   //government unemployment benefits equal 0
	v[10]=v[3];                                            //government consumption equal desired
	v[11]=v[4];                                            //government investment equal desired
	v[12]=v[5];                                            //government intermediate demand equals desired
}
else
{
	v[8]=min(v[0],v[1]);								   //government wages is desired limited by maximum expenses
	v[9]=min(v[2],(v[0]-v[8]));    						   //government unemployment benefits is desired limited by maximum expenses minus wages
	v[10]=min(v[3],(v[0]-v[8]-v[9]));       			   //government consumption is desired limited by maximum expenses minus wages and benefits
	v[11]=min(v[4],(v[0]-v[8]-v[9]-v[10]));        		   //government investment is desired limited by maximum expenses minus wages and benefits
	v[12]=min(v[5],(v[0]-v[8]-v[9]-v[10]-v[11]));          //government intermediate is desired limited by maximum expenses minus wages and benefits
}

WRITE("Government_Effective_Wages", max(0,v[8]));
WRITE("Government_Effective_Unemployment_Benefits",  max(0,v[9]));
WRITE("Government_Effective_Consumption",  max(0,v[10]));
WRITE("Government_Effective_Investment",  max(0,v[11]));
WRITE("Government_Effective_Inputs",  max(0,v[12]));
v[13]=max(0,(v[8]+v[9]+v[10]+v[11]+v[12]));
RESULT(v[13])

EQUATION_DUMMY("Government_Effective_Wages","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Unemployment_Benefits","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Consumption","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Investment","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Inputs","Government_Effective_Expenses")


EQUATION("Government_Income_Taxes")
RESULT(SUMS(country,"Class_Taxation"))

EQUATION("Government_Indirect_Taxes")
RESULT(SUMS(country,"Sector_Taxation"))

EQUATION("Government_Total_Taxes")
RESULT(V("Government_Income_Taxes")+V("Government_Indirect_Taxes"))

EQUATION("Government_Primary_Result")
RESULT(V("Government_Total_Taxes")-V("Government_Effective_Expenses"))

EQUATION("Government_Interest_Payment")
RESULT(V("Basic_Interest_Rate")*max(0,VL("Government_Debt",1)))

EQUATION("Government_Nominal_Result")
RESULT(V("Government_Primary_Result")-V("Government_Interest_Payment"))

EQUATION("Government_Debt")
RESULT(CURRENT-V("Government_Nominal_Result"))

EQUATION("Government_Debt_GDP_Ratio")
	v[0]=V("annual_frequency");
	v[1]=V("Government_Debt");
	v[2]=0;
	for(i=0; i<=v[0]-1; i++)
		v[2]=v[2]+VL("Country_GDP",i);
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])

	













