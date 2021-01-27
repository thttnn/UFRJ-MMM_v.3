/*****PUBLIC SECTOR*****/

EQUATION("Government_Desired_Wages")
/*
Priority expenses.
If there are no maximum expenses, it is adjusted by average productivity growth and inflation.
*/

v[0]=V("government_period");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust government wages)
{
	v[3]=VL("Country_Avg_Productivity",1);                     //avg productivity lagged 1
	v[4]=VL("Country_Avg_Productivity", v[0]);                 //avg productivity lagged government period (4)
	v[5]= v[4]!=0? (v[3]-v[4])/v[4] : 0;                       //calculate productivity growth
	v[8]=VS(financial, "target_inflation");
	v[9]=V("government_productivity_passtrought");             //productivity passtrough parameter
	v[10]=V("government_inflation_passtrought");			   //inflation passtrough to public wages
	v[11]=V("government_real_growth");
	v[12]=v[2]*(1+v[9]*v[5]+v[10]*v[8]+v[11]);                 //desired adjusted government wages with no restriction
}
else                                                           //if it is not adjustment period
	v[12]=v[2];                                                //use last period's
RESULT(v[12])


EQUATION("Government_Desired_Unemployment_Benefits")
/*
Counter-cyclical Expenses
Benefit is a share of average wage. 
The amount depends on current unemployment.
*/
v[0]=V("government_period");
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
v[0]=V("government_period");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(capital, "Sector_Avg_Price",1);                         
	v[6]=VLS(capital, "Sector_Avg_Price", v[0]);                  		
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(v[8])


EQUATION("Government_Desired_Consumption")
/*
Desired Consumption Expenses
Adjusted by a desired real growth rate and avg consumption price growth
*/
v[0]=V("government_period");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(consumption, "Sector_Avg_Price",1);                         
	v[6]=VLS(consumption, "Sector_Avg_Price", v[0]);       
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(v[8])


EQUATION("Government_Desired_Inputs")
/*
Desired Intermediate Expenses
Adjusted by a desired real growth rate and avg input price growth
*/
v[0]=V("government_period");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=V("government_real_growth");
	v[5]=VLS(input, "Sector_Avg_Price",1);                         
	v[6]=VLS(input, "Sector_Avg_Price", v[0]);       
	v[7]= v[6]!=0? (v[5]-v[6])/v[6] : 0;
	v[8]=v[2]*(1+v[3]+v[7]);
}
else
	v[8]=v[2];
RESULT(v[8])


EQUATION("Government_Surplus_Rate_Target")
/*
Adjusts government surplus target based on debt to gdp evolution
*/
v[0]=V("government_period");
v[1]= fmod((double) t,v[0]);                                   //divides the time period by government adjustment period (adjust annualy)
v[2]=CURRENT;                   							   //last period's target
if(v[1]==0)                                                    //if the rest of the division is zero (adjust unemployment benefits)
{
	v[3]=VL("Government_Debt_GDP_Ratio",1);                    //current debt to gdp ratio
	v[8]=VL("Government_Debt_GDP_Ratio",v[0]);
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


EQUATION("Government_Max_Expenses")
/*
Maximum Government expenses imposed by the fiscal rule.
Fiscal rules can be two types: primary surplus target or expenses ceiling (or both).
Depend on the policy parameter.
*/

v[0]=V("begin_surplus_target_rule");                           //define when surplus target rule begins
v[1]=V("begin_expenses_ceiling_rule");                         //define when expenses ceiling begins
v[2]=V("government_period");
v[3]= fmod((double) t,v[2]);                                   //divides the time period by government adjustment period (adjust annualy)
if(v[3]==0)                                                    //if the rest of the division is zero (adjust maximum expenses)
{                                                              //adjust fiscal rules maximum expenses
		v[4]=VL("Country_GDP", 1);                                      //GDP lagged 1
		v[5]=VL("Country_GDP", v[2]);                                   //GDP lagged government period (4)
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
		v[13]=VL("Country_Consumer_Price_Index", v[2]);                 //consumer price index lagged government period (4)
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
RESULT(v[16])


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
	v[10]=min(v[3],(v[0]-v[8]-v[9])*(v[14]/v[17]));        //government consumption is desired limited by maximum expenses minus wages and benefits
	v[11]=min(v[4],(v[0]-v[8]-v[9])*(v[15]/v[17]));        //government investment is desired limited by maximum expenses minus wages and benefits
	v[12]=min(v[5],(v[0]-v[8]-v[9])*(v[16]/v[17]));        //government intermediate is desired limited by maximum expenses minus wages and benefits
}
WRITE("Government_Effective_Wages", v[8]);
WRITE("Government_Effective_Unemployment_Benefits", v[9]);
WRITE("Government_Effective_Consumption", v[10]);
WRITE("Government_Effective_Investment", v[11]);
WRITE("Government_Effective_Inputs", v[12]);
v[13]=v[8]+v[9]+v[10]+v[11]+v[12];
RESULT(v[13])

EQUATION_DUMMY("Government_Effective_Wages","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Unemployment_Benefits","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Consumption","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Investment","Government_Effective_Expenses")
EQUATION_DUMMY("Government_Effective_Inputs","Government_Effective_Expenses")


EQUATION("Government_RND");
/*
Share of government wages, consequently distributed to income classes as normal wages.
*/
	v[0]=V("Government_Effective_Wages");					//government effective wages
	v[1]=V("government_rnd_share");							//fixed share of effective wages allocated to rnd
	v[2]=1-exp(-v[0]*v[1]);									//probability of success, based on effective rnd expenses
	if(RND<v[2])                              				//draws a random number. if it is lower then innovation probability
	{
		v[3]=V("government_std_dev_innovation");        	//innovation standard deviation
		v[4]=V("government_initial_productivity");			//initial frontier productivity
		v[5]=V("goverment_tech_opportunity_productivity"); 	//technological opportunity for process innovation
		v[6]=log(v[4])+(double)t*(v[5]);        			//the average of the innovation distribution will be the initial frontier productivity plus the opportunity parameter times the time period
		v[7]=exp(norm(v[6],v[3]));             				//the innovation productivity will be a draw from a normal distribution with average depending of the tech regime and std. dev fixed
	}  	
  	else                                      				//if the random number is not lower than imitation probability
     	v[7]=0; 
RESULT(v[7])


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
	v[1]=V("Government_Debt");
	v[2]=V("Country_GDP");
	v[3]= v[2]!=0? v[1]/v[2] : 0;
RESULT(v[3])















