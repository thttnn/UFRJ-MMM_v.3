/*****PRODUCTION AND DEMAND*****/


EQUATION("Sector_Intermediate_Demand")
/*
This stores the value of the "Dom_Intermediate_Demand_Function" for each sector.
*/
	v[0]=V("id_intermediate_goods_sector");
	if(v[0]==1)
		v[1]=V("Total_Domestic_Intermediate_Demand");
	else
		v[1]=0;
RESULT(v[1])


EQUATION("Sector_Consumption_Demand") 
/*
Stores the value of the Demand Function if it is a consumption goods sector
*/
	v[0]=V("id_consumption_goods_sector");                  	//identifies consumption goods sector
	if(v[0]==1)                                             	//if it is a consumption good sector
		v[1]=V("Total_Domestic_Consumption_Demand");       	//stores the value of the function  
	else                                                    	//if it is not a consumption good sector 
		v[1]=0;                                               	//domestic consumption is zero
RESULT(v[1])


EQUATION("Sector_Capital_Demand")
/*
Calls the Capital_Goods_Demand Function and calculates the demand of other sectors.
*/
	v[0]=V("id_capital_goods_sector");
	if(v[0]==1)
		v[1]=V("Total_Domestic_Capital_Goods_Demand");
	else
		v[1]=0;
RESULT(v[1])


EQUATION("Sector_Effective_Orders")
/*
Effective orders are determined from total demand for the products in the sector. In the sum of consumption goods, capital goods and intermediate goods, only the factor referring to the sector that is calling this variable will asume positive values. In the case of the agricultural sector, effective orders also include exports.
*/
	v[0]=V("Sector_Consumption_Demand");                                                       //domestic demand of consumption goods
	v[1]=V("Sector_Capital_Demand");                                                           //domestic demand of capital goods
	v[2]=V("Sector_Intermediate_Demand");                                                      //domestic demand of intermediate goods
	v[3]=v[0]+v[1]+v[2];                                                                         //sums up the domestic demands. For each sector, only the relevant demand will have a value and the others will be zero.
	v[4]=V("Sector_Exports");                                                                    //external demand, exports of the sector (zero for the non-agricultural sector)
	v[5]=v[3]+v[4];                                                                              //sums up domestic and external demand
	if(v[5]!=0)
		v[6]=v[4]/v[5];
	else
		v[6]=0;
	WRITE("Sector_Exports_Share", v[6]);
RESULT(max(0,v[5]))

EQUATION_DUMMY("Sector_Exports_Share", "Sector_Effective_Orders")


EQUATION("Firm_Effective_Orders_Capital_Goods")
/*
Firm variable
It is settled in a way that there will be no excess demand while there is still productive capacity in the sector. This distribution is done in this variable.
*/
	
	v[1]=V("id_capital_goods_sector");   
	if(v[1]==1)
	{
		v[2]=V("Firm_Market_Share"); 
		v[3]=V("Sector_Effective_Orders");
		v[4]=v[3]*v[2];
	}
	else
		v[4]=0;      
RESULT(v[4])






