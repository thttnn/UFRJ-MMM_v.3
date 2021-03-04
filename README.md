# MMM_v.3.6
Multisectoral Micro-Macro Model Version 3.6 (Finance Augmented)

## WHAT'S NEW?

Introduction of Banking System
* N number of Bank Agents
* Basileia-type Regulatory Rule
* Financial Fragility Sensitivity

Endogeneization of Firm's and Classes Financial Decisions
* Desired Debt Rate
* Liquidity Preference

Introduction of Financial Costs to Firms

Introduction of Interest Rate Structure
* Basic Interest Rate Following Possible Monetary Policy Rules
* Deposits Spread
* Short-Term Loans Spread
* Long-Term Loans Spread
* Individual Risk-Premium

Introduction of Some Analysis Variables
* Firm's Financial Positions (Hedge, Speculative, Ponzi)
* Bankrupt events counter
* Bank and Financial Sector Variables

For more information on previous versions: <https://thttnn.github.io/MMM_CORE/>

### BANKING SYSTEM:
The banking system is composed by a pre-determined number of banks, which collect deposits from firms and income classes and provide loans to them. 
The number of banks is fixed and they all start equally.
Firm-bank relationships are determined randomly at the beginning of the simulation run, but after, the probability is weighted by bank's market-share.
Firm-bank relationships are fixed for the simulation run.
Income classes deposits, interest and loans are distributed to banks by market-share.
Banks have a limit to total credit based on basileia-type regulatory rule, net worth and individual financial fragility sensitivities.
However, credit rationing affects bank's competitiveness negativelly, as well as defaulted loans. 

### INTEREST RATE STRUCTURE:
Banks set deposits and short-term interest rates by simply applying a markup or markdown on basis interest rate.
Long-term interest rates are adjusted by bank's market-share. Therefore, the higher the concentration, higher is the average long-term rate.
Basic Interest Rate depends on the monetary policy rule.

### FIRM'S FINANCIAL DECISIONS:
Firms can adjust (or not) desired debt rate and liquidity preference (as a share of capital) based on net profits growth.
Firms can adjust extra amortization (or not) based on current and desired debt rate.
Firms can incorporate (or not) financial costs to unit variable cost if current debt rate is higher than desired.
Income classes can also adjust desired debt rate and liquidity preference based on net income growth.


