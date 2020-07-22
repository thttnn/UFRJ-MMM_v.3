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
* Extra Debt Amortization

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

**Control Parameters**: 
* "number_object_banks": determines the initial number of banks (fixed, no entry or exit). [Baseline=5]
* "minimum_capital_ratio": regulatory rule. If 0, no total credit limit. [Baseline=0.05]

**Other Relevant Parameters**:
* "fragility_sensitivity": determines bank's total credit sensitivity to overall financial fragility of the economy.
* "default_sensitivity":  determines bank's total credit sensitivity to individual financial fragility of the bank.
* "e_loans": determines the competitiveness elasticity to defaulted loans
* "e_interest": determines the competitiveness elasticity to interest rate

### INTEREST RATE STRUCTURE:
Banks set deposits and short-term interest rates by simply applying a markup or markdown on basis interest rate.
Long-term interest rates are adjusted by bank's market-share. Therefore, the higher the concentration, higher is the average long-term rate.
Basic Interest Rate depends on the monetary policy rule.

**Control Parameters**: 
* "real_interest_rate": determines the initial real interest rate. [Baseline=0.0025]
* "deposits_spread": determines the mark down to interest on deposits
* "short_term_loans_spread":  determines the markup to interest on short-term loans
* "long_term_loans_spread": determines the  basic markup to interest on long-term loans
* "risk_premium_adjustment": determines how risk premium is sensitive to individual risks
* "parameter2": determines the weights of the long-term interest rate setting

### FIRM'S FINANCIAL DECISIONS:
Firms can adjust (or not) desired debt rate and liquidity preference (as a share of capital) based on net profits growth.
Firms can adjust extra amortization (or not) based on current and desired debt rate.
Firms can incorporate (or not) financial costs to unit variable cost if current debt rate is higher than desired.
Income classes can also adjust desired debt rate and liquidity preference based on net income growth.

**Control Parameters**: 
* "firm_debt_rate_adjustment": determines how firms adjust desired debt rate if net profits are growing or decreasing. If 0, desired debt rate is fixed. [Baseline=0.01]
* "firm_liquidity_preference_adjustment": determines how firms adjust liquidity preference if net profits are growing or decreasing. If 0, liquidity preference is fixed. [Baseline=0]
* "firms_debt_payment_adjustment": determines how firms repay additional debt if current debt rate is higher than desired. If 0, no extra amortization, fixed. [Baseline=0]
* "class_debt_rate_adjustment": determines how classes adjust desired debt rate if net profits are growing or decreasing. If 0, desired debt rate is fixed. [Baseline=0]
* "class_liquidity_preference_adjustment": determines how classes adjust liquidity preference if net profits are growing or decreasing. If 0, liquidity preference is fixed. [Baseline=0]
* "financial_cost_weight": determines how much firms weight financial costs if current debt rate is higher than desired. [Baseline=0]

**Other Relevant Parameters**:
* "initial_class_liquidity_preference": relevant if "class_liquidity_preference_adjustment" is zero. [Baseline=0.05]
* "initial_class_desired_debt_rate":  relevant if "class_debt_rate_adjustment" is zero. [Baseline=0.5]
* "initial_firm_liquidity_preference": relevant if "firm_liquidity_preference_adjustment" is zero. [Baseline=0.05]
* "initial_firm_desired_debtr_rate": relevant if "firm_debt_rate_adjustment" is zero. [Baseline=0.5]
* "initial_firm_extra_debt_payment": relevant if "class_debt_rate_adjustment" is zero. [Baseline=0]

