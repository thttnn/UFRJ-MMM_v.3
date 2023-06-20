library(tidyverse)
library(readxl)
sim <- read_xlsx("sim.xlsx")
annual <- sim %>% 
  group_by(Year) %>% 
  summarise(GDP = sum(Sim_GDP),
            Energy = sum(Sim_Energy),
            Emissions = sum(Sim_Emissions))

annual <- annual %>% 
  mutate(EI = Energy/GDP,
         CI = Emissions/GDP)

growth <- annual %>% 
  mutate(GDP_g = log(GDP) - lag(log(GDP),1),
         Energy_g = log(Energy) - lag(log(Energy),1),
         Emissions_g = log(Emissions) - lag(log(Emissions),1),
         CI_g = log(CI) - lag(log(CI),1),
         EI_g = log(EI) - lag(log(EI),1)) %>% 
  drop_na()
         
growth %>% 
  filter(Year !=51) %>% 
  select(GDP_g, Energy_g, Emissions_g, CI_g, EI_g) %>% 
  summarise(avg_gdp_g = mean(GDP_g),
            avg_energy_g = mean(Energy_g),
            avg_emissions_g = mean(Emissions_g),
            avg_ci_g = mean(CI_g),
            avg_ei_g = mean(EI_g))
         
         
         
         
