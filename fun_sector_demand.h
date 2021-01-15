/*****PRODUCTION AND DEMAND*****/


EQUATION("Sector_External_Price")
/*
External price of the sector's goods. 
*/
	v[0]=VL("Sector_External_Price",1);
	v[1]=V("sector_external_price_growth");
	if(v[1]!=0)	
		v[2]=(1+v[1])*v[0];
	else
   	{     
		v[3]=VL("Sector_Avg_Price",2);
		v[4]=VL("Sector_Avg_Price",1);
		v[5]=V("sector_external_price_competitiveness");
		v[2]=v[0]*(1+v[5]*((v[4]-v[3])/v[3]));
   	}  
RESULT(v[2])


EQUATION("Sector_Real_Exports")
/*
Exports are defined for each sector based on the application of an export coefficient on external income. The division by price observed in the past period allows to transform the value of exports into units of exported products.
*/
	v[0]=V("External_Income");
	v[1]=V("sector_exports_coefficient");
	v[2]=V("Sector_Avg_Price");
	v[3]=V("Sector_External_Price");
	v[4]=V("sector_exports_elasticity_income");
	v[5]=V("sector_exports_elasticity_price");
	v[6]=V("Exchange_Rate");
	v[7]=v[1]*pow((v[3]*v[6])/v[2],v[5])*pow(v[0],v[4]);
	v[8]=v[7]/v[2];
	v[9]=V("switch_fixed_exports");
	if(v[9]==1)
		v[10]=CURRENT;
	else	
		v[10]=v[8];
RESULT(v[10])


EQUATION("Sector_Effective_Orders")
/*
Effective orders are determined from total demand for the products in the sector. In the sum of consumption goods, capital goods and intermediate goods, only the factor referring to the sector that is calling this variable will asume positive values. In the case of the agricultural sector, effective orders also include exports.
*/
	if(V("id_intermediate_goods_sector")==1)
		v[3]=V("Country_Domestic_Intermediate_Demand");                                                       
	if(V("id_consumption_goods_sector")==1)
		v[3]=V("Country_Domestic_Consumption_Demand");                                                          
	if(V("id_capital_goods_sector")==1)
		v[3]=V("Country_Domestic_Capital_Goods_Demand");                                                    
	v[4]=V("Sector_Real_Exports");                                                                    //external demand, exports of the sector (zero for the non-agricultural sector)
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

EQUATION("Sector_Extra_Imports")
/*
The extra import, if the sector can not meet its internal demand, is determined by the difference between the actual orders of the sector and its actual production plus the available stock of products. The value of these imports is obtained by multiplying the previous result by the external price of the inputs of the sector in question.
*/
	if(V("id_intermediate_goods_sector")==1)
		v[0]=V("Country_Domestic_Intermediate_Demand");                                                       
	if(V("id_consumption_goods_sector")==1)
		v[0]=V("Country_Domestic_Consumption_Demand");                                                          
	if(V("id_capital_goods_sector")==1)
		v[0]=V("Country_Domestic_Capital_Goods_Demand");
	v[3]=V("Sector_Demand_Met");
	v[4]=v[0]*(1-v[3]);
	v[5]=VL("International_Reserves",1);
	if(v[4]>0)
		{
		if(v[5]>0)
			{
			v[6]=v[4];
			v[7]=1;
			}
		else
			{
			v[6]=0;
			v[7]=0;
			}
		WRITE("Sector_Demand_Met_By_Imports", v[7]);
		}
	else
		v[6]=0;
RESULT(v[6])

EQUATION_DUMMY("Sector_Demand_Met_By_Imports", "Sector_Extra_Imports")




