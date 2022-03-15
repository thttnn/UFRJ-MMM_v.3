#******************************************************************
#
# ----------------- MMM.V.3 Aggregates analysis ---------------
#
#******************************************************************

# ------------ Read Monte Carlo experiment files ----------------

folder    <- "./FiscalMultiplierTripodFixedSurplusTarget"                  # data files folder
baseName  <- "Sim_"                     # data files base name (same as .lsd file)
nExp      <- 4                      # number of experiments (sensitivity/different cases)
iniDrop   <- 0                          # initial time steps to drop from analysis (0=none)
nKeep     <- -1                         # number of time steps to keep (-1=all)
cores     <- 0                          # maximum number of cores to allocate (0=all)
savDat    <- F                          # save processed data files and re-use if available?

expVal <- c( #"Baseline",
             "S1",
             "S2",
             "S3",
             "S4",
             "S5",
             "S6",
             "0.028",
             "0.032",
             "0.036",
             "S10")                   # case parameter values

# ------------ Define Variables ----------------
# Rate variables to use (Variables in Rate)
aggrVars <-  c(   "GDP_G",        # Annual Real GDP Growth
                  "P_G",          # Annual Overall Price Growth, Inflation
                  "CPI_G",        # Annual CPI Growth, Inflation
                  "PSH",          # Profit Share 
                  "WSH",          # Wage Share
                  "PCU",          # Productive Capacity Utilization
                  "PR",           # Profit Rate
                  "MK",           # Average Markup
                  "CGDP",         # Consumption Share of GDP
                  "IGDP",         # Investment Share of GDP
                  "GGDP",         # Government Expenses Share of GDP
                  "NXGDP",        # Net Exports Share of GDP
                  "XGDP",         # Exports Share of GDP
                  "MGDP",         # Imports Share of GDP
                  "INVGDP",       # Inventories Share of GDP
                  "KGDP",         # Capital Stock Share of GDP (K/Y Ratio)
                  "FS_DMET",      # Financial Sector Demand Met (Credit Rationing)
                  "DEBT_FS_G",    # Stock of Loans Growth Rate
                  "DEBT_FS_ST_G", # Stock of Short term loans Growth Rate
                  "DEBT_FS_LT_G", # Stock of Long Term Loans Growth Rate
                  "DEP_FS_G",     # Stock of Deposits Growth Rate
                  "DEBT_RT_FI",   # Avg Firm Debt Rate
                  "DEBT_RT_CL",   # Avg Classes Debt Rate
                  "FS_HHI",       # Financial Sector Inverse HHI (Concentration)
                  "FS_LEV",       # Financial Sector Leverage
                  "FS_STR",       # Financial Sector Short Term Rate
                  "FS_DR",        # Financial Sector Default Rate
                  "PONZI",        # Share of Ponzi Firms
                  "SPEC",         # Share of Speculative Firms
                  "HEDGE",        # Share of Hedge Firms
                  "IR",           # Basic Interest Rate
                  "IR_DEP",       # Deposits Interest Rate
                  "IR_ST",        # Base Short Term Interest Rate
                  "IR_LT",        # Base Long Term Interest Rate
                  "Cri",          # Crisis Counters
                  "BKR",          # Number of Bankrupts
                  "BKR_RT",       # Bankrupts Rate, as a share of the number of firms.
                  "PST",          # Primary Surplus Target
                  "PS_GDP",       # Effective Primary Surplus to GDP
                  "PDEBT_GDP",    # Public Debt to GDP Ratio
                  "RES_GDP",      # International Reserves to GDP Ratio
                  "DX_GDP",       # External Debt to GDP Ratio
                  "EMP",          # Employment in Hours of Labor
                  "ER",           # Exchange Rate
                  "GDP_r",        # Real GDP
                  "C_r",          # Real Consumption
                  "I_r",          # Real Investment
                  "G_r",          # Real Government Expenses
                  "M_r",          # Real Imports
                  "X_r",          # Real Exports
                  "NX_r",         # Real Net Exports
                  "K_r",          # Real Stock of Capital
                  "INVE_r",       # Real Stock of Inventories
                  "P",            # Price Index
                  "PROFITS",      # Real Profits
                  "WAGE",         # Real Wages
                  "PROD",         # Average Labor Productivity
                  "KL",           # Capital Labor Ratio
                  "DEBT_FS",      # Total Stock of Loans
                  "DEBT_FS_ST",   # Total Stock of Short Term Loans
                  "DEBT_FS_LT",   # Total Stock of Long Term Loans
                  "DEP_FS",       # Total Stock of Deposits
                  "FS_PR" ,       # Financial Sector Nominal Profits
                  "FS_RES",       # Financial Sector CB Rescue
                  "FS_DEF",       # Financial Sector Defaulted Loans
                  "G",            # Nominal Government Effective Expenses
                  "TT",           # Nominal Goverment Total Taxes
                  "DT",           # Nominal Government Direct Taxes
                  "IT",           # Nominal Government Indirect Taxes
                  "PDEBT",        # Nominal Stock of Public Debt
                  "GDPX_r",       # Real External Income     
                  "X",            # Nominal Exports
                  "M",            # Nominal Imports
                  "NX",           # Nominal Trade Balance
                  "CF",           # Nominal Net Capital Flows
                  "RES",          # Nominal Stock of International Reserves
                  "GINI",         # Gini Index
                  "P_C",          # Consumption sector Avg. Price
                  "P_K",          # Capital sector Avg. Price
                  "P_I",          # Intermediate sector Avg. Price
                  "W_C",          # Consumption sector Avg. Wage
                  "W_K",          # Capital sector Avg. Wage
                  "W_I",          # Intermediate sector Avg. Wage
                  "MK_C",         # Consumption sector Avg. Markup
                  "MK_K",         # Capital sector Avg. Markup
                  "MK_I",         # Intermediate sector Avg. Markup
                  "PROD_C",       # Consumption sector Avg. Productivity
                  "PROD_K",       # Capital sector Avg. Productivity
                  "PROD_I",       # Intermediate sector Avg. Productivity
                  "U_C",          # Consumption sector Unemployment
                  "U_K",          # Capital sector Unemployment
                  "U_I",          # Intermediate sector Unemployment
                  "HHI_C",        # Consumption sector HHI
                  "HHI_K",        # Capital sector HHI
                  "HHI_I",        # Intermediate sector HHI
                  "PX_C",         # Consumption sector External Price
                  "PX_K",         # Capital sector External Price
                  "PX_I",         # Intermediate sector External Price
                  "DEBT_RT_C",    # Consumption sector Avg. Debt Rate
                  "DEBT_RT_K",    # Capital sector Avg. Debt Rate
                  "DEBT_RT_I",    # Intermediate sector Avg. Debt Rate
                  "IRST_C",       # Consumption sector Avg. Short Term Interest Rate
                  "IRST_K",       # Capital sector Avg. Short Term Interest Rate
                  "IRST_I",       # Intermediate sector Avg. Short Term Interest Rate
                  "IRLT_C",       # Consumption sector Avg. Long Term Interest Rate
                  "IRLT_K",       # Capital sector Avg. Long Term Interest Rate
                  "IRLT_I",       # Intermediate sector Avg. Long Term Interest Rate
                  "GDP",          # Nominal GDP
                  "C",            # Nominal Consumption
                  "I",            # Nominal Investment
                  "Country_GDP",
                  "Country_Annual_GDP",
                  "Country_Annual_Real_GDP",
                  "IR" ,           # Basic Interest Rate
                  "Government_Effective_Wages",
                  "Government_Effective_Consumption",
                  "Government_Effective_Inputs",
                  "Government_Effective_Investment",
                  "GW_r",
                  "GI_r"
              ) 


# Temporary data file suffix
datFilSfx <- "_aggr.Rdata"

# ==== Log start mark ====

cat( "\nMicro-macro aggregates analysis\n=======================\n" )
cat( "\n", as.character( Sys.time( ) ), "-> Start processing...\n\n" )
startTime <- proc.time( )       # register current time
options( warn = -1 )

# ==== Read command line parameters (if any) ====
args <- commandArgs( trailingOnly = TRUE )
cat( "Command line arguments: ", args, "\n" )

if( length ( args ) > 0 ){  # first parameter has to be the folder
  folder <- args [1]
}
if( length ( args ) > 1 ){  # second parameter has to be the base name
  baseName <- args [2]
}
if( length ( args ) > 2 ){  # third parameter has to be the number of experiments
  nExp <- as.integer( args [3] )
}
if( length ( args ) > 3 ){  # fourth parameter has to be the initial time period ( 0 is all )
  iniDrop <- as.integer( args [4] )
}
if( length ( args ) > 4 ){  # fifth parameter has to be the end periods to remove ( -1 is all )
  nKeep <- as.integer( args [5] )
}
if( length ( args ) > 5 ){  # sixth parameter has to be the number of cores ( 0 is all )
  cores <- as.integer( args [6] )
}
if( length ( args ) > 6 ){  # seventh parameter has to be the intermediate data saving flag
  savDat <- as.logical( args [7] )
}

cat( " Folder =", folder, "\n" )
cat( " Base name =", baseName, "\n" )
cat( " Number of experiments =", nExp, "\n" )
cat( " Initial time steps to drop =", iniDrop, "\n" )
cat( " Time steps to keep =", nKeep, "\n" )
cat( " Maximum cores to use =", cores, "\n" )
cat( " Re-use data files =", savDat, "\n\n" )

# ==== Process LSD result files ====
# Package with LSD interface functions
library( LSDinterface, verbose = FALSE, quietly = TRUE )
library( parallel, verbose = FALSE, quietly = TRUE )

# ==== Read data files ----

# Function to read one experiment data (to be parallelized)
readExp <- function( exper ) {
  if( nExp > 1 ) {
    myFiles <- list.files( path = folder, pattern = paste0( baseName, exper, "_[0-9]+.res" ),
                           full.names = TRUE )
  } else {
    myFiles <- list.files( path = folder, pattern = paste0( baseName, "_[0-9]+.res" ),
                           full.names = TRUE )
  }
  
  if( length( myFiles ) < 1 )
    stop( "Data files not found. Check 'folder', 'baseName' and 'nExp' parameters." )
  
  cat( "\nData files: ", myFiles, "\n" )
  
  # Read data from text files and format it as a 3D array with labels
  mc <- read.3d.lsd( myFiles, aggrVars, skip = iniDrop, nrows = nKeep, nnodes = lsdCores )
  
  # Get dimensions information
  nTsteps <- dim( mc )[ 1 ]              # number of time steps
  nVar <- dim( mc )[ 2 ]                 # number of variables
  nSize  <- dim( mc )[ 3 ]               # Monte Carlo sample size
  
  cat( "\nData details:\n" )
  cat( " Number of MC cases =", nSize, "\n" )
  cat( " Number of variables =", nVar, "\n" )
  cat( " Number of used periods =", nTsteps, "\n\n" )
  
  # Compute Monte Carlo averages and std. deviation and store in 2D arrrays
  stats <- info.stats.lsd( mc )
  
  # Insert a t column
  t <- as.integer( rownames( stats$avg ) )
  A <- as.data.frame( cbind( t, stats$avg ) )
  S <- as.data.frame( cbind( t, stats$sd ) )
  M <- as.data.frame( cbind( t, stats$max ) )
  m <- as.data.frame( cbind( t, stats$min ) )
  
  # Write to the disk as (European) CSV files for Excel
  write.csv( A, paste0( folder, "/", baseName, exper, "_aggr_avg.csv" ),
             row.names = FALSE, quote = FALSE )
  write.csv( S, paste0( folder, "/", baseName, exper, "_aggr_sd.csv" ),
             row.names = FALSE, quote = FALSE )
  write.csv( M, paste0( folder, "/", baseName, exper, "_aggr_max.csv" ),
             row.names = FALSE, quote = FALSE )
  write.csv( m, paste0( folder, "/", baseName, exper, "_aggr_min.csv" ),
             row.names = FALSE, quote = FALSE )
  
  # Save temporary results to disk to save memory
  tmpFile <- paste0( folder, "/", baseName, exper, datFilSfx )
  save( mc, A, S, M, m, nTsteps, nVar, nSize, file = tmpFile )
  
  return( tmpFile )
}

# only reprocess results file if requested/needed
if( savDat ) {
  
  tmpFiles <- list( )
  noDat <- FALSE
  
  # check all .dat files exist and are newer than .res files
  for( i in 1 : nExp ) {
    tmpFiles[[ i ]] <- paste0( folder, "/", baseName, i, datFilSfx )
    if( ! file.exists( tmpFiles[[ i ]] ) )
      noDat <- TRUE
    else {
      myFiles <- list.files( path = folder, pattern = paste0( baseName, i, "_[0-9]+.res" ),
                             full.names = TRUE )
      # if any .res file is newer, redo everything
      if( length( myFiles ) > 0 &&
          max( file.mtime( myFiles ) ) > file.mtime( tmpFiles[[ i ]] ) ) {
        if( ! noDat )
          cat( "New data files detected, removing previously saved data...\n\n" )
        unlink( tmpFiles[[ i ]] )
        noDat <- TRUE
      }
    }
  }
  
  if( ! noDat )
    cat( "Re-using previously saved data...\n" )
}

if( ! savDat || noDat ) {
  
  cat( "Reading data from files...\n" )
  
  # configure clusters for 2 level parallel loading
  if( cores == 0 )
    cores <- detectCores( )
  cores <- min( cores, detectCores( ) )
  lsdCores <- 1
  if( cores != 1 ) {
    # fully allocate cores (round up to ensure 100% utilization)
    if( cores > nExp )
      lsdCores <- ceiling( cores / nExp )
    
    # initiate cluster for parallel loading
    cl <- makeCluster( min( nExp, cores ) )
    
    # configure cluster: export required variables & packages
    clusterExport( cl, c( "nExp", "folder", "baseName", "aggrVars", "iniDrop",
                          "nKeep", "datFilSfx", "lsdCores" ) )
    invisible( clusterEvalQ( cl, library( LSDinterface ) ) )
    
    # load each experiment in parallel
    tmpFiles <- parLapplyLB( cl, 1 : nExp, readExp )
    
    stopCluster( cl )
    
  } else {
    
    # load each experiment serially
    tmpFiles <- lapply( 1 : nExp, readExp )
  }
}

# ==== Organize data read from files ----

# fill the lists to hold data
mcData <- list() # 3D Monte Carlo data
Adata <- list()  # average data
Sdata <- list()  # standard deviation data
Mdata <- list()  # maximum data
mdata <- list()  # minimum data
nTsteps.1 <- nSize.1 <- 0

for( k in 1 : nExp ) {                      # realocate data in separate lists
  
  load( tmpFiles[[ k ]] )                   # pick data from disk
  if( ! savDat )
    file.remove( tmpFiles[[ k ]] )          # and delete temporary file, if needed
  
  if( k > 1 && ( nTsteps != nTsteps.1 || nSize != nSize.1 ) )
    stop( "Inconsistent data files.\nSame number of time steps and of MC runs is required." )
  
  mcData[[ k ]] <- mc
  rm( mc )
  Adata[[ k ]] <- A
  Sdata[[ k ]] <- S
  Mdata[[ k ]] <- M
  mdata[[ k ]] <- m
  nTsteps.1 <- nTsteps
  nSize.1 <- nSize
}

# free memory
rm( tmpFiles, A, S, M, m, nTsteps.1, nSize.1 )
invisible( gc( verbose = FALSE ) )

# ==== External support files  ======

library("LSDsensitivity")
source( "support-functions.R" )

# ===================== User parameters =========================

bCase     <- 1      # experiment to be used as base case
CI        <- 0.95   # desired confidence interval
warmUpPlot<- 100    # number of "warm-up" runs for plots
nTplot    <- 600     # last period to consider for plots (-1=all)
warmUpStat<- 200    # warm-up runs to evaluate all statistics
nTstat    <- 600     # last period to consider for statistics (-1=all)
bPlotCoef <- 1.5    # boxplot whiskers extension from the box (0=extremes)
bPlotNotc <- FALSE  # use boxplot notches
lowP      <- 6      # bandpass filter minimum period
highP     <- 32     # bandpass filter maximum period
bpfK      <- 12     # bandpass filter order
lags      <- 4      # lags to analyze
smoothing <- 1600   # HP filter smoothing factor (lambda)
crisisTh  <- 0.00   # crisis growth threshold
crisisLen <- 3      # crisis minimum duration (periods)
crisisPre <- 4      # pre-crisis period to base trend start (>=1)
crisisRun <- 0      # the crisis case to be plotted (0=auto)
crisesPlt <- TRUE   # plot all the crisis plots in a separate pdf file?

repName   <- baseName  # report files base name (if "" same baseName)
sDigits   <- 4      # significant digits in tables
transMk   <- -1     # regime transition mark after warm-up (-1:none)
plotRows  <- 1      # number of plots per row in a page
plotCols  <- 1  	  # number of plots per column in a page
plotW     <- 10     # plot window width
plotH     <- 7      # plot window height
raster    <- TRUE  # raster or vector plots
res       <- 600    # resolution of raster mode (in dpi)

# Colors assigned to each experiment's lines in graphics
colors <- c( "black", "blue", "red", "orange", "green", "brown", "yellow", "purple", "gray", "blueviolet" )
#colors <- rep( "black", 6 )

# Line types assigned to each experiment
lTypes <- c( "solid", "solid", "solid", "solid", "solid", "solid", "solid", "solid", "solid", "solid")
#lTypes <- c( "solid", "dashed", "dotted", "dotdash", "longdash", "twodash" )

# Point types assigned to each experiment
pTypes <- c( 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 )
#pTypes <- c( 4, 0, 1, 2, 3, 5 )



# ===================== Time Plot Function ====

time_plots <- function( mcData, Adata, mdata, Mdata, Sdata, nExp, nSize, nTsteps,
                        TmaskPlot, CI, legends, colors, lTypes, transMk, smoothing,
                        firmTypes ) {
  
  # ------ GDP, consumption and investment cases comparison charts ------
  
  # ------ GDP, consumption and investment cases comparison charts ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$GDP_r[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$GDP_r[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$GDP_r[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$GDP_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$GDP_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Value",
              tit = " Real GDP",
              subtit = paste( "MC runs =", nSize ))
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$I_r[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$C_r[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$GDP_r[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$I_r[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$C_r[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$GDP_r[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$I_r[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$C_r[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$I_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$I_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$C_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$C_r[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$I_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$I_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$C_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$C_r[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = " Real GDP, Investment and Consumption",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "GDP", "Investment", "Consumption" ) )
  
  # ------ GDP, consumption and investment cases comparison charts ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$GDP[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$I[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$C[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$GDP[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$I[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$C[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$GDP[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$I[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$C[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$GDP[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$I[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$I[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$C[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$C[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$GDP[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$I[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$I[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$C[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$C[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Nominal GDP, Investment and Consumption",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "GDP", "Investment", "Consumption" ) )
  
  
  
  # ------ Exports and Imports------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$M[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$X[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$M[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$X[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$M[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$X[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$M[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$M[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$X[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$X[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$M[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$M[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$X[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$X[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Imports and Exports",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Imports", "Exports" ) )
  
  # ------ Balance of Payments ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$NX[ TmaskPlot ] ,
                         Adata[[ k ]]$CF[ TmaskPlot ]  )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$NX[ TmaskPlot ] ,
                        mdata[[ k ]]$CF[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$NX[ TmaskPlot ] ,
                        Mdata[[ k ]]$CF[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$NX[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$NX[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$CF[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CF[ TmaskPlot ]  / sqrt( nSize )  )
    hi[[ k ]] <- list( Adata[[ k ]]$NX[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$NX[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$CF[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CF[ TmaskPlot ]  / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Value",
              tit = "Balance of Payments",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Net Exports", "Net Capital Flows" ) )
  
  # ------ Exchange Rate  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$ER[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$ER[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$ER[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$ER[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$ER[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$ER[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$ER[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Exchange Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ International Reserves to GDP  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$RES_GDP[ TmaskPlot ],
                         Adata[[ k ]]$DX_GDP[ TmaskPlot ])
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$RES_GDP[ TmaskPlot ],
                        mdata[[ k ]]$DX_GDP[ TmaskPlot ])
    max[[ k ]] <- list( Mdata[[ k ]]$RES_GDP[ TmaskPlot ],
                        Mdata[[ k ]]$DX_GDP[ TmaskPlot ])
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$RES_GDP[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$RES_GDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$DX_GDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DX_GDP[ TmaskPlot ] / sqrt( nSize ))
    hi[[ k ]] <- list( Adata[[ k ]]$RES_GDP[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$RES_GDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$DX_GDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DX_GDP[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "International Reserves and External Debt GDP Ratios",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Reserves", "External Debt" ) )
  
  
  
  # ------ External Income ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$GDPX_r[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$GDP_r[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$GDPX_r[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$GDP_r[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$GDPX_r[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$GDPX_r[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDPX_r[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$GDP_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDP_r[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$GDPX_r[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GDPX_r[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Domestic and External Real GDP",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Domestic", "External" ) )
  
  # ------ Government Expenses and Taxes ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$G[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$TT[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$G[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$TT[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$G[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$TT[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$G[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$G[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$TT[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$TT[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$G[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$G[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$TT[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$TT[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Government Expenses and Total Taxes",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Government Expenses", "Total Taxes" ) )
  
  # ------ Primary Surplus ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$PS_GDP[ TmaskPlot ] ,
                         Adata[[ k ]]$PST[ TmaskPlot ]  )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$PS_GDP[ TmaskPlot ] ,
                        mdata[[ k ]]$PST[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$PS_GDP[ TmaskPlot ] ,
                        Mdata[[ k ]]$PST[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$PS_GDP[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PS_GDP[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$PST[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PST[ TmaskPlot ]  / sqrt( nSize )  )
    hi[[ k ]] <- list( Adata[[ k ]]$PS_GDP[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PS_GDP[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$PST[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PST[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Primary Surplus to GDP",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Effective Primary Surplus", "Target" ) )
  
  # ------ Public Debt to GDP  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$PDEBT_GDP[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$PDEBT_GDP[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$PDEBT_GDP[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$PDEBT_GDP[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PDEBT_GDP[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$PDEBT_GDP[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PDEBT_GDP[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Public Debt to GDP Ratio",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Shares of GDP------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    
    exps[[ k ]] <- list( Adata[[ k ]]$CGDP[ TmaskPlot ], 
                         Adata[[ k ]]$IGDP[ TmaskPlot ], 
                         Adata[[ k ]]$GGDP[ TmaskPlot ],
                         Adata[[ k ]]$XGDP[ TmaskPlot ],
                         Adata[[ k ]]$MGDP[ TmaskPlot ])
    
    # minimum and maximum MC runs
    
    min[[ k ]] <- list( mdata[[ k ]]$CGDP[ TmaskPlot ],
                        mdata[[ k ]]$IGDP[ TmaskPlot ],
                        mdata[[ k ]]$GGDP[ TmaskPlot ],
                        mdata[[ k ]]$XGDP[ TmaskPlot ],
                        mdata[[ k ]]$MGDP[ TmaskPlot ])
    
    max[[ k ]] <- list( Mdata[[ k ]]$CGDP[ TmaskPlot ],
                        Mdata[[ k ]]$IGDP[ TmaskPlot ],
                        Mdata[[ k ]]$GGDP[ TmaskPlot ],
                        Mdata[[ k ]]$XGDP[ TmaskPlot ],
                        Mdata[[ k ]]$MGDP[ TmaskPlot ])
    
    # MC confidence interval
    
    lo[[ k ]] <- list( Adata[[ k ]]$CGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$GGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$XGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$XGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$MGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MGDP[ TmaskPlot ] / sqrt( nSize ))
    
    hi[[ k ]] <- list( Adata[[ k ]]$CGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$GGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$XGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$XGDP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$MGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MGDP[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Shares",
              tit = "Shares of GDP",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Investment", "Government", "Exports", "Imports" ) )
  
  # ------ Inflation ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$P_G[ TmaskPlot ])
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$P_G[ TmaskPlot ])
    max[[ k ]] <- list( Mdata[[ k ]]$P_G[ TmaskPlot ])
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$P_G[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_G[ TmaskPlot ] / sqrt( nSize ))
    hi[[ k ]] <- list( Adata[[ k ]]$P_G[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_G[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "GDP Deflator",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Inflation ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$CPI_G[ TmaskPlot ])
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$CPI_G[ TmaskPlot ])
    max[[ k ]] <- list( Mdata[[ k ]]$CPI_G[ TmaskPlot ])
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$CPI_G[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CPI_G[ TmaskPlot ] / sqrt( nSize ))
    hi[[ k ]] <- list( Adata[[ k ]]$CPI_G[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$CPI_G[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "CPI Inflation",
              subtit = paste( "MC runs =", nSize ) )
  
  
  # ------ Wages and Profits Shares------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    
    exps[[ k ]] <- list( Adata[[ k ]]$WSH[ TmaskPlot ], 
                         Adata[[ k ]]$PSH[ TmaskPlot ])
    
    # minimum and maximum MC runs
    
    min[[ k ]] <- list( mdata[[ k ]]$WSH[ TmaskPlot ],
                        mdata[[ k ]]$PSH[ TmaskPlot ] )
    
    max[[ k ]] <- list( Mdata[[ k ]]$WSH[ TmaskPlot ],
                        Mdata[[ k ]]$PSH[ TmaskPlot ])
    
    # MC confidence interval
    
    lo[[ k ]] <- list( Adata[[ k ]]$WSH[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$WSH[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$PSH[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PSH[ TmaskPlot ] / sqrt( nSize ))
    
    hi[[ k ]] <- list( Adata[[ k ]]$WSH[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$WSH[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$PSH[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PSH[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Shares",
              tit = "Wages and Profits",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Wages", "Profits" ) )
  
  
  # ------ Gini ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$GINI[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$GINI[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$GINI[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$GINI[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GINI[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$GINI[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$GINI[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Index",
              tit = "Gini Index on Income",
              subtit = paste( "MC runs =", nSize ) )
  
  
  
  
  # ------ Productivity  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$PROD[ TmaskPlot ] ))
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$PROD[ TmaskPlot ] ))
    max[[ k ]] <- list( log0( Mdata[[ k ]]$PROD[ TmaskPlot ] ))
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$PROD[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PROD[ TmaskPlot ] / sqrt( nSize ) ))
    hi[[ k ]] <- list( log0( Adata[[ k ]]$PROD[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PROD[ TmaskPlot ] / sqrt( nSize ) ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Log",
              tit = "Average Productivity",
              subtit = paste( "MC runs =", nSize ) )
  
  
  # ------ Markup  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$MK[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$MK[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$MK[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$MK[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$MK[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Value",
              tit = "Average Mark-up",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Profit Rate  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$PR[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$PR[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$PR[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$PR[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PR[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$PR[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PR[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Profit Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Capacity Utilization  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$PCU[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$PCU[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$PCU[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$PCU[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PCU[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$PCU[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PCU[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Capacity Utilization",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Capital Stock to GDP  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$KGDP[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$KGDP[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$KGDP[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$KGDP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$KGDP[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$KGDP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$KGDP[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Capital Stock to GDP",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Capital Labor Ratio  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$KL[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$KL[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$KL[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$KL[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$KL[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$KL[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$KL[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Capital Labor Ratio",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Firms Debt Rate  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_FI[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Firms Avg. Debt Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Class Debt Rate  ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_CL[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Households Avg. Debt Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Stock of Loans and Deposits------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$DEBT_FS[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$DEP_FS[ TmaskPlot ] ))
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$DEBT_FS[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$DEP_FS[ TmaskPlot ] ))
    max[[ k ]] <- list( log0( Mdata[[ k ]]$DEBT_FS[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$DEP_FS[ TmaskPlot ] ))
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$DEBT_FS[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_FS[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$DEP_FS[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEP_FS[ TmaskPlot ] / sqrt( nSize ) ))
    hi[[ k ]] <- list( log0( Adata[[ k ]]$DEBT_FS[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_FS[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$DEP_FS[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEP_FS[ TmaskPlot ] / sqrt( nSize ) ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Log",
              tit = "Total Stock of Loans and Deposits",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Loans", "Deposits" ))
  
  
  # ------ Stock of Loans Growth ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$DEBT_FS_G[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$DEBT_FS_G[ TmaskPlot ] )
    max[[ k ]] <- list( Mdata[[ k ]]$DEBT_FS_G[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$DEBT_FS_G[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_FS_G[ TmaskPlot ] / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$DEBT_FS_G[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_FS_G[ TmaskPlot ] / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Loans Growth",
              subtit = paste( "MC runs =", nSize ) )
  
  
  
  # ------ Leverage ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$FS_LEV[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$FS_LEV[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$FS_LEV[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$FS_LEV[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_LEV[ TmaskPlot ] / sqrt( nSize  ) )
    hi[[ k ]] <- list( Adata[[ k ]]$FS_LEV[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_LEV[ TmaskPlot ] / sqrt( nSize  ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Value",
              tit = "Financial Sector Leverage",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Financial Sector Demand Met ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$FS_DMET[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$FS_DMET[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$FS_DMET[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$FS_DMET[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_DMET[ TmaskPlot ] / sqrt( nSize  ) )
    hi[[ k ]] <- list( Adata[[ k ]]$FS_DMET[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_DMET[ TmaskPlot ] / sqrt( nSize  ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Financial Sector Demand Met",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Financial Sector Profits ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$FS_PR[ TmaskPlot ] ))
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$FS_PR[ TmaskPlot ] ))
    max[[ k ]] <- list( log0( Mdata[[ k ]]$FS_PR[ TmaskPlot ] ))
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$FS_PR[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_PR[ TmaskPlot ] / sqrt( nSize ) ))
    hi[[ k ]] <- list( log0( Adata[[ k ]]$FS_PR[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_PR[ TmaskPlot ] / sqrt( nSize ) ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Log",
              tit = "Financial Sector Profits",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Financial Sector Default Rate ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$FS_DR[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$FS_DR[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$FS_DR[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$FS_DR[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_DR[ TmaskPlot ] / sqrt( nSize  ) )
    hi[[ k ]] <- list( Adata[[ k ]]$FS_DR[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_DR[ TmaskPlot ] / sqrt( nSize  ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Financial Sector Default Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Fiancial Postures------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    
    exps[[ k ]] <- list( Adata[[ k ]]$PONZI[ TmaskPlot ], 
                         Adata[[ k ]]$SPEC[ TmaskPlot ],
                         Adata[[ k ]]$HEDGE[ TmaskPlot ])
    
    # minimum and maximum MC runs
    
    min[[ k ]] <- list( mdata[[ k ]]$PONZI[ TmaskPlot ],
                        mdata[[ k ]]$SPEC[ TmaskPlot ],
                        mdata[[ k ]]$HEDGE[ TmaskPlot ] )
    
    max[[ k ]] <- list( Mdata[[ k ]]$PONZI[ TmaskPlot ],
                        Mdata[[ k ]]$SPEC[ TmaskPlot ],
                        Mdata[[ k ]]$HEDGE[ TmaskPlot ])
    
    # MC confidence interval
    
    lo[[ k ]] <- list( Adata[[ k ]]$PONZI[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PONZI[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$SPEC[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$SPEC[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$HEDGE[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HEDGE[ TmaskPlot ] / sqrt( nSize ))
    
    hi[[ k ]] <- list( Adata[[ k ]]$PONZI[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PONZI[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$SPEC[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$SPEC[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$HEDGE[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HEDGE[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Shares",
              tit = "Financial Positions",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Ponzi", "Speculative", "Hedge" ) )
  
  # ------ Basic Interest Rate ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$IR[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$IR[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR[ TmaskPlot ] / sqrt( nSize  ) )
    hi[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR[ TmaskPlot ] / sqrt( nSize  ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Basic Interest Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Interest Rate Structure------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    
    exps[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ], 
                         Adata[[ k ]]$IR_DEP[ TmaskPlot ], 
                         Adata[[ k ]]$IR_ST[ TmaskPlot ],
                         Adata[[ k ]]$IR_LT[ TmaskPlot ])
    
    # minimum and maximum MC runs
    
    min[[ k ]] <- list( mdata[[ k ]]$IR[ TmaskPlot ],
                        mdata[[ k ]]$IR_DEP[ TmaskPlot ],
                        mdata[[ k ]]$IR_ST[ TmaskPlot ],
                        mdata[[ k ]]$IR_LT[ TmaskPlot ])
    
    max[[ k ]] <- list( Mdata[[ k ]]$IR[ TmaskPlot ],
                        Mdata[[ k ]]$IR_DEP[ TmaskPlot ],
                        Mdata[[ k ]]$IR_ST[ TmaskPlot ],
                        Mdata[[ k ]]$IR_LT[ TmaskPlot ])
    
    # MC confidence interval
    
    lo[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_DEP[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_DEP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_ST[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_ST[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_LT[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_LT[ TmaskPlot ] / sqrt( nSize ))
    
    hi[[ k ]] <- list( Adata[[ k ]]$IR[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_DEP[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_DEP[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_ST[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_ST[ TmaskPlot ] / sqrt( nSize ),
                       Adata[[ k ]]$IR_LT[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IR_LT[ TmaskPlot ] / sqrt( nSize ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Shares",
              tit = "Interest Rate Structure",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Central Bank", "Deposits", "Short Term", "Long Term" ) )
  
  # ------ Bankrupt Rate ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$BKR_RT[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$BKR_RT[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$BKR_RT[ TmaskPlot ] )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$BKR_RT[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$BKR_RT[ TmaskPlot ] / sqrt( nSize  ) )
    hi[[ k ]] <- list( Adata[[ k ]]$BKR_RT[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$BKR_RT / sqrt( nSize  ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Bankrupt Rate",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Banking Crisis ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$FS_RES[ TmaskPlot ] ))
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$FS_RES[ TmaskPlot ] ))
    max[[ k ]] <- list( log0( Mdata[[ k ]]$FS_RES[ TmaskPlot ] ))
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$FS_RES[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_RES[ TmaskPlot ] / sqrt( nSize ) ))
    hi[[ k ]] <- list( log0( Adata[[ k ]]$FS_RES[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$FS_RES[ TmaskPlot ] / sqrt( nSize ) ))
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Log",
              tit = "Banking Crisis",
              subtit = paste( "MC runs =", nSize ) )
  
  # ------ Sectoral Prices ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$P_C[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$P_K[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$P_I[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$P_C[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$P_K[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$P_I[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$P_C[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$P_K[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$P_I[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$P_C[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_C[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$P_K[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_K[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$P_I[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_I[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$P_C[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_C[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$P_K[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_K[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$P_I[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$P_I[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Sectoral Average Prices",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral External Prices ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( log0( Adata[[ k ]]$PX_C[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$PX_K[ TmaskPlot ] ),
                         log0( Adata[[ k ]]$PX_I[ TmaskPlot ] ) )
    # minimum and maximum MC runs
    min[[ k ]] <- list( log0( mdata[[ k ]]$PX_C[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$PX_K[ TmaskPlot ] ),
                        log0( mdata[[ k ]]$PX_I[ TmaskPlot ] ) )
    max[[ k ]] <- list( log0( Mdata[[ k ]]$PX_C[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$PX_K[ TmaskPlot ] ),
                        log0( Mdata[[ k ]]$PX_I[ TmaskPlot ] ) )
    # MC confidence interval
    lo[[ k ]] <- list( log0( Adata[[ k ]]$PX_C[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_C[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$PX_K[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_K[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$PX_I[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_I[ TmaskPlot ]  / sqrt( nSize ) ) )
    hi[[ k ]] <- list( log0( Adata[[ k ]]$PX_C[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_C[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$PX_K[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_K[ TmaskPlot ] / sqrt( nSize ) ),
                       log0( Adata[[ k ]]$PX_I[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$PX_I[ TmaskPlot ]  / sqrt( nSize ) ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Logs",
              tit = "Sectoral External Prices",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Wages ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$W_C[ TmaskPlot ] ,
                         Adata[[ k ]]$W_K[ TmaskPlot ] ,
                         Adata[[ k ]]$W_I[ TmaskPlot ]  )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$W_C[ TmaskPlot ] ,
                        mdata[[ k ]]$W_K[ TmaskPlot ] ,
                        mdata[[ k ]]$W_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$W_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$W_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$W_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$W_C[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$W_K[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$W_I[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$W_C[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$W_K[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$W_I[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$W_I[ TmaskPlot ]  / sqrt( nSize ) )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Sectoral Average Wage Rate",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Markups ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$MK_C[ TmaskPlot ] ,
                         Adata[[ k ]]$MK_K[ TmaskPlot ] ,
                         Adata[[ k ]]$MK_I[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$MK_C[ TmaskPlot ] ,
                        mdata[[ k ]]$MK_K[ TmaskPlot ] ,
                        mdata[[ k ]]$MK_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$MK_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$MK_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$MK_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$MK_C[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$MK_K[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$MK_I[ TmaskPlot ] -
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$MK_C[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$MK_K[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$MK_I[ TmaskPlot ] +
                               qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$MK_I[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Sectoral Average Markup",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Concentration ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$HHI_C[ TmaskPlot ] ,
                         Adata[[ k ]]$HHI_K[ TmaskPlot ] ,
                         Adata[[ k ]]$HHI_I[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$HHI_C[ TmaskPlot ] ,
                        mdata[[ k ]]$HHI_K[ TmaskPlot ] ,
                        mdata[[ k ]]$HHI_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$HHI_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$HHI_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$HHI_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$HHI_C[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$HHI_K[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$HHI_I[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$HHI_C[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$HHI_K[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$HHI_I[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$HHI_I[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Index",
              tit = "Sectoral Inverse HHI",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Short Term Interest ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$IRST_C[ TmaskPlot ] ,
                         Adata[[ k ]]$IRST_K[ TmaskPlot ] ,
                         Adata[[ k ]]$IRST_I[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$IRST_C[ TmaskPlot ] ,
                        mdata[[ k ]]$IRST_K[ TmaskPlot ] ,
                        mdata[[ k ]]$IRST_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$IRST_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$IRST_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$IRST_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$IRST_C[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRST_K[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRST_I[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$IRST_C[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRST_K[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRST_I[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRST_I[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Sectoral Average Short Term Interest Rate",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Long Term Interest ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$IRLT_C[ TmaskPlot ] ,
                         Adata[[ k ]]$IRLT_K[ TmaskPlot ] ,
                         Adata[[ k ]]$IRLT_I[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$IRLT_C[ TmaskPlot ] ,
                        mdata[[ k ]]$IRLT_K[ TmaskPlot ] ,
                        mdata[[ k ]]$IRLT_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$IRLT_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$IRLT_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$IRLT_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$IRLT_C[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRLT_K[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRLT_I[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$IRLT_C[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRLT_K[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$IRLT_I[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$IRLT_I[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Sectoral Average Long Term Interest Rate",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  # ------ Sectoral Debt Rate ------
  
  exps <- min <- max <- lo <- hi <- list( )
  # select data to plot
  for( k in 1 : nExp ){
    # MC averages
    exps[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_C[ TmaskPlot ] ,
                         Adata[[ k ]]$DEBT_RT_K[ TmaskPlot ] ,
                         Adata[[ k ]]$DEBT_RT_I[ TmaskPlot ] )
    # minimum and maximum MC runs
    min[[ k ]] <- list( mdata[[ k ]]$DEBT_RT_C[ TmaskPlot ] ,
                        mdata[[ k ]]$DEBT_RT_K[ TmaskPlot ] ,
                        mdata[[ k ]]$DEBT_RT_I[ TmaskPlot ]  )
    max[[ k ]] <- list( Mdata[[ k ]]$DEBT_RT_C[ TmaskPlot ] ,
                        Mdata[[ k ]]$DEBT_RT_K[ TmaskPlot ] ,
                        Mdata[[ k ]]$DEBT_RT_I[ TmaskPlot ]  )
    # MC confidence interval
    lo[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_C[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$DEBT_RT_K[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$DEBT_RT_I[ TmaskPlot ] -
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_I[ TmaskPlot ]  / sqrt( nSize ) )
    hi[[ k ]] <- list( Adata[[ k ]]$DEBT_RT_C[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_C[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$DEBT_RT_K[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_K[ TmaskPlot ] / sqrt( nSize ) ,
                       Adata[[ k ]]$DEBT_RT_I[ TmaskPlot ] +
                         qnorm(1 - (1 - CI ) / 2) * Sdata[[ k ]]$DEBT_RT_I[ TmaskPlot ]  / sqrt( nSize )  )
  }
  
  plot_lists( exps, min, max, lo, hi, leg = legends, mrk = transMk, col = colors,
              lty = lTypes, xlab = "Time", ylab = "Rate",
              tit = "Sectoral Average Debt Rate",
              subtit = paste( "MC runs =", nSize ),
              leg2 = c( "Consumption", "Capital", "Intermediate" ) )
  
  
}

# ===================== Box Plot Function ====

box_plots <- function( mcData, nExp, nSize, TmaxStat, TmaskStat, warmUpStat,
                       nTstat, legends, legendList, sDigits, bPlotCoef,
                       bPlotNotc, folder, outDir, repName ) {
  
  # ======= COMPARISON OF EXPERIMENTS =======
  
  numStats <- 99
  statsTb <- array( dim = c( numStats, 4, nExp ) )
  statsBp <- array( dim = c( numStats, 5, nExp ) )
  n <- array( dim = c( numStats, nExp ) )
  conf <- array( dim = c( numStats, 2, nExp ) )
  out <- array( list( ), dim = c( numStats, nExp ) )
  names <- units <- list( )
  
  # ---- Collect the data for each experiment ----
  
  for( k in 1 : nExp ) {
    stat <- 0
    temp <- matrix( nrow = TmaxStat, ncol = nSize )
    
    stat <- stat + 1
    names[[ stat ]] <- "GDP Growth"
    units[[ stat ]] <- "Average GDP Growth rate"
    temp <- mcData[[ k ]][ TmaskStat, "GDP_G", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Volatility of GDP Growth"
    units[[ stat ]] <- "Standard deviation of GDP growth rate"
    temp <- mcData[[ k ]][ TmaskStat, "GDP_G", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colSds( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Capacity Utilization"
    units[[ stat ]] <- "Average Capacity Utilization Rate"
    temp <- mcData[[ k ]][ TmaskStat, "PCU", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Volatility of Capacity Utilization"
    units[[ stat ]] <- "Average Capacity Utilization Rate"
    temp <- mcData[[ k ]][ TmaskStat, "PCU", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colSds( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Likelihood of Crisis"
    units[[ stat ]] <- "Likelihood of Crisis"
    temp <- mcData[[ k ]][ TmaskStat, "Cri", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "CPI Inflation"
    units[[ stat ]] <- "Consumer prices index average growth rate"
    temp <- mcData[[ k ]][ TmaskStat, "CPI_G", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Volatility of CPI Inflation"
    units[[ stat ]] <- "Consumer prices index average growth rate"
    temp <- mcData[[ k ]][ TmaskStat, "CPI_G", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colSds( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Inflation"
    units[[ stat ]] <- "GDP Deflator average growth rate"
    temp <- mcData[[ k ]][ TmaskStat, "P_G", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Exchange Rate"
    units[[ stat ]] <- "Exchange Rate"
    temp <- mcData[[ k ]][ TmaskStat, "ER", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Volatility of Exchange Rate"
    units[[ stat ]] <- "Exchange Rate"
    temp <- mcData[[ k ]][ TmaskStat, "ER", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colSds( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "International Reserves/GDP"
    units[[ stat ]] <- "International Reserves/GDP rate"
    temp <- mcData[[ k ]][ TmaskStat, "RES_GDP", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Primary Surplus/GDP"
    units[[ stat ]] <- "Primary Surplus/GDP rate"
    temp <- mcData[[ k ]][ TmaskStat, "PS_GDP", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Government Debt/GDP"
    units[[ stat ]] <- "Government Debt/GDP rate"
    temp <- mcData[[ k ]][ TmaskStat, "PDEBT_GDP", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Profit Rate"
    units[[ stat ]] <- "Average Profit Rate"
    temp <- mcData[[ k ]][ TmaskStat, "PR", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Profit Share"
    units[[ stat ]] <- "Average Profit Share"
    temp <- mcData[[ k ]][ TmaskStat, "PSH", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Wage Share"
    units[[ stat ]] <- "Average Wage Share"
    temp <- mcData[[ k ]][ TmaskStat, "WSH", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] )
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Basic Interest Rate"
    units[[ stat ]] <- "Central Bank Basic Interest Rate"
    temp <- mcData[[ k ]][ TmaskStat, "IR", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Volatility of Basic Interest Rate"
    units[[ stat ]] <- "Basic Interest Rate SD"
    temp <- mcData[[ k ]][ TmaskStat, "IR", ]
    temp[ ! is.finite( temp ) ] <- NA
    x <- colSds( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Firms Avg Debt Rate"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "DEBT_RT_FI", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
   
    stat <- stat + 1
    names[[ stat ]] <- "Classes Avg Debt Rate"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "DEBT_RT_CL", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
  
    stat <- stat + 1
    names[[ stat ]] <- "Financial Sector Default Rate"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "FS_DR", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Financial Sector Demand Met"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "FS_DMET", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Share of Ponzi Firms"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "PONZI", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Share of Speculative Firms"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "SPEC", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Share of Hedge Firms"
    units[[ stat ]] <- "Average rate"
    temp <- mcData[[ k ]][ TmaskStat, "HEDGE", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
    stat <- stat + 1
    names[[ stat ]] <- "Bankrupt Rate"
    units[[ stat ]] <- "Bankrupt Rate"
    temp <- mcData[[ k ]][ TmaskStat, "BKR_RT", ]
    temp[is.infinite(temp)] <- sign(temp[is.infinite(temp)] ) 
    x <- colMeans( temp, na.rm = TRUE )
    bPlotStats <- boxplot.stats( x, coef = bPlotCoef )
    statsTb[ stat, , k ] <- c( mean( x ), sd( x ), min( x ), max( x ) )
    statsBp[ stat, , k ] <- bPlotStats$stats
    n[ stat, k ] <- bPlotStats$n
    conf[ stat, , k ] <- bPlotStats$conf
    out[[ stat, k ]] <- bPlotStats$out
    
  }
  
  # remove unused stats space
  numStats <- stat
  stat <- stat + 1
  statsTb <- statsTb[ - ( stat : 99 ), , ]
  statsBp <- statsBp[ - ( stat : 99 ), , ]
  n <- n[ - ( stat : 99 ), ]
  conf <- conf[ - ( stat : 99 ), , ]
  out <- out[ - ( stat : 99 ), ]
  rm( temp, x )
  
  
  # ---- Build experiments statistics table and performance comparison chart ----
  
  table.stats <- statsTb[ , , 1 ]
  table.names <- c( "Avg[1]", "SD[1]", "Min[1]", "Max[1]" )
  perf.comp <- statsTb[ , 1, 1 ]
  perf.names <- c( "Baseline[1]" )
  
  # Print whisker plots for each statistics
  
  for( stat in 1 : numStats ) {
    
    # find max/mins for all experiments
    LowLim <- Inf
    upLim <- -Inf
    for( k in 1 : nExp ) {
      if( conf[ stat, 1, k ] < LowLim )
        lowLim <- conf[ stat, 1, k ]
      if( conf[ stat, 2, k ] > upLim )
        upLim <- conf[ stat, 2, k ]
    }
    upLim <- upLim + ( upLim - lowLim )
    lowLim <- lowLim - ( upLim - lowLim )
    
    # build the outliers vectors
    outVal <- outGrp <- vector( "numeric" )
    for( k in 1 : nExp ) {
      if( length( out[[ stat, k ]] ) == 0 )
        next
      outliers <- vector( "numeric" )
      for( i in 1 : length( out[[ stat, k ]] ) ) {
        if( out[[ stat, k ]][ i ] < upLim &&
            out[[ stat, k ]][ i ] > lowLim )
          outliers <- append( outliers, out[[ stat, k ]][ i ] )
      }
      if( length( outliers ) > 0 ) {
        outVal <- append( outVal, outliers )
        outGrp <- append( outGrp, rep( k, length( outliers ) ) )
      }
    }
    
    listBp <- list( stats = statsBp[ stat, , ], n = n[ stat, ], conf = conf[ stat, , ],
                    out = outVal, group = outGrp, names = legends )
    title <- names[[ stat ]]
    subTitle <- as.expression(bquote(paste( "( bar: median / box: 2nd-3rd quartile / whiskers: max-min / points: outliers / MC runs = ",
                                            .( nSize ), " / period = ", .( warmUpStat + 1 ), " - ",
                                            .( nTstat ), " )" ) ) )
    tryCatch( bxp( listBp, range = bPlotCoef, notch = bPlotNotc, main = title,
                   sub = subTitle, ylab = units[[ stat ]] ),
              error = function( e ) {
                warning( "In boxplot (bxp): problem while plotting: ", title, "\n\n" )
                textplot( paste( "Plot for <", title, "> failed." ) )
              } )
  }
  
  if( nExp > 1 ){
    
    # Create 2D stats table and performance comparison table
    
    for(k in 2 : nExp){
      
      # Stats table
      table.stats <- cbind( table.stats, statsTb[ , , k ] )
      table.names <- cbind( table.names, c( paste0( "Avg[", k, "]" ),
                                            paste0( "SD[", k, "]" ),
                                            paste0( "Min[", k, "]" ),
                                            paste0( "Max[", k, "]" ) ) )
      
      # Performance comparison table
      perf.comp <- cbind( perf.comp, statsTb[ , 1, k ] / statsTb[ , 1, 1 ] )
      t <- ( statsTb[ , 1, k ] - statsTb[ , 1, 1 ] ) /
        sqrt( ( statsTb[ , 2, k ] ^ 2 + statsTb[ , 2, 1 ] ^ 2 ) / nSize )
      df <- floor( ( ( statsTb[ , 2, k ] ^ 2 + statsTb[ , 2, 1 ] ^ 2 ) / nSize ) ^ 2 /
                     ( ( 1 / ( nSize - 1 ) ) * ( ( statsTb[ , 2, k ] ^ 2 / nSize ) ^ 2 +
                                                   ( statsTb[ , 2, 1 ] ^ 2 / nSize ) ^ 2 ) ) )
      pval <- 2 * pt( - abs ( t ), df )
      perf.comp <- cbind( perf.comp, pval )
      perf.names <- cbind( perf.names, t( c( paste0( "Ratio[", k, "]" ),
                                             paste0( "p-val[", k, "]" ) ) ) )
    }
  }
  
  # Print experiments table
  colnames( table.stats ) <- table.names
  rownames( table.stats ) <- names
  
  textplot( formatC( table.stats, digits = sDigits, format = "g" ), cmar = 1 )
  title <- paste( "Monte Carlo descriptive statistics ( all experiments )" )
  subTitle <- paste( "( numbers in brackets indicate the experiment number / MC runs =",
                     nSize, "/ period =", warmUpStat + 1, "-", nTstat, ")" )
  title( main = title, sub = subTitle )
  mtext( legendList, side = 1, line = -2, outer = TRUE )
  
  # Write table to the disk as CSV files for Excel
  write.csv( table.stats, quote = FALSE,
             paste0( folder, "/", baseName, outDir, "/", repName, "_exps_stats.csv" ) )
  
  if( nExp > 1 ) {
    
    # Experiments performance comparison table
    
    colnames( perf.comp ) <- perf.names
    rownames( perf.comp ) <- names
    
    textplot( formatC( perf.comp, digits = sDigits, format = "g" ), cmar = 1 )
    title <- paste( "Performance comparison ( all experiments )" )
    subTitle <- paste( "( numbers in brackets indicate the experiment number / H0: no difference with baseline / MC runs =",
                       nSize, "/ period =", warmUpStat + 1, "-", nTstat, ")" )
    title( main = title, sub = subTitle )
    mtext( legendList, side = 1, line = -2, outer = TRUE )
    
    # Write table to the disk as CSV files for Excel
    write.csv( perf.comp, quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, "_perf_comp.csv" ) )
  }
}


# ==== More Support stuff ====

if( repName == "" )
  repName <- baseName

# Generate fancy labels & build labels list legend
legends <- vector( )
legendList <- "Experiments: "
for( k in 1 : nExp ) {
  if( is.na( expVal[ k ] ) || expVal[ k ] == "" )
    legends[ k ] <- paste( "Case", k )
  else
    legends[ k ] <- expVal[ k ]
  if( k != 1 )
    legendList <- paste0( legendList, ",  " )
  legendList <- paste0( legendList, "[", k, "] ", legends[ k ] )
}

# Number of periods to show in graphics and use in statistics
if( nTplot < 1 || nTplot > nTsteps || nTplot <= warmUpPlot )
  nTplot <- nTsteps
if( nTstat < 1 || nTstat > nTsteps || nTstat <= warmUpStat )
  nTstat <- nTsteps
if( nTstat < ( warmUpStat + 2 * bpfK + 4 ) )
  nTstat <- warmUpStat + 2 * bpfK + 4         # minimum number of periods
TmaxStat <- nTstat - warmUpStat
TmaskPlot <- ( warmUpPlot + 1 ) : nTplot
TmaskStat <- ( warmUpStat + 1 ) : nTstat
TmaskBpf <- ( bpfK + 1 ) : ( TmaxStat - bpfK )

# Calculates the critical correlation limit for significance (under heroic assumptions!)
critCorr <- qnorm( 1 - ( 1 - CI ) / 2 ) / sqrt( nTstat )



# ==== Main code ====

tryCatch({    # enter error handling mode so PDF can be closed in case of error/interruption
  
  # ====== CREATE DIRECTORY AND SELECT OUTPUT TYPE ======

  outDir <- format( Sys.time(), "%Y-%m-%d" )
  if( ! dir.exists( paste0( folder, "/", baseName, outDir ) ) )
    dir.create( paste0( folder, "/", baseName, outDir ) )
  
  cat( paste( "\nSaving results and data to:", paste0( folder, "/", baseName, outDir ), "\n" ) )
  
  # Select type of output
  if( raster ){
    # Open PNG (bitmap) files for output
    png( paste0( folder, "/", baseName, outDir, "/", repName, "_aggr_plots_%d.png" ),
         width = plotW, height = plotH, units = "in", res = res )
    TRUE
  } else {
    # Open PDF plot file for output
    pdf( paste0( folder, "/", baseName, outDir, "/", repName, "_aggr_plots.pdf" ),
         width = plotW, height = plotH )
    par( mfrow = c ( plotRows, plotCols ) )             # define plots per page
    png( paste0( folder, "/", baseName, outDir, "/", repName, "_aggr_plots_%d.png" ),
         width = plotW, height = plotH, units = "in", res = res )
  }
  
  # ====== PLOTS GENERATION ======

  cat( "\nProcessing experiments and generating reports...\n")
  
  time_plots( mcData, Adata, mdata, Mdata, Sdata, nExp, nSize, nTsteps, TmaskPlot,
              CI, legends, colors, lTypes, transMk, smoothing )
  
  if(nExp>1)
  {
  box_plots( mcData, nExp, nSize, TmaxStat, TmaskStat, warmUpStat,
                         nTstat, legends, legendList, sDigits, bPlotCoef,
                         bPlotNotc, folder, outDir, repName )
  }
  
  # ====== STATISTICS GENERATION ======
  
  # Create vectors and lists to hold the Monte Carlo results
  gdp_growth<- 
  capacity_utilization<-
  crisis<-
  inflation<- 
  inflation_cpi<- 
  exchange_rate<-
  reserves_ratio<-
  primary_surplus_ratio<-
  pubic_debt_ratio<-
  profit_rate<-
  profit_share<- 
  wage_share<- 
  debt_rate_firms<-
  debt_rate_class<-
  ponzi_rate <- 
  speculative_rate <- 
  hedge_rate <-
  financial_demand_met<-
  bankrupt_rate<-
  consumption_gdp<-
  investment_gdp<-
  government_gdp<- 
  netexports_gdp<-
  inventories_gdp<- 
  capital_gdp<-
  vector( mode = "numeric", length = nSize )
  
  gdp_bpf_sd<-
  c_bpf_sd<-
  i_bpf_sd<-
  g_bpf_sd<-
  m_bpf_sd<-
  x_bpf_sd<-
  nx_bpf_sd<-
  p_bpf_sd<-
  k_sd<-
  inve_sd<-
  emp_bpf_sd<-
  pr_bpf_sd<-
  wg_bpf_sd <-
  pcu_bpf_sd<-
  dr_bpf_sd<-
  lev_bpf_sd<-
    ir_bpf_sd<-
  pr_sh_sd<-
  wg_sh_sd<-
  prod_sd<-
  mk_sd<-
  kl_sd<-
  infla_sd<-
  u_sd<-
  pcu_sd<-
  pr_sd<-
  cgdp_sd<-
  igdp_sd<-
  ggdp_sd<-
  nxgdp_sd<-
  invgdp_sd<-
  kgdp_sd<-
  debtfs_sd<-
  debtfs_st_sd<-
  debtfs_lt_sd<-
  depfs_sd<-
  drtc_sd<-
  drtk_sd<-
  drti_sd<-
  drt_fi_sd<-
  drt_cl_sd<-
  fshhi_sd<-
  fslev_sd<-
  fsstr_sd<-
  fsdr_sd<-
  fspr_sd<-
  fsdef_sd<-
  ponzi_sd<-
  spec_sd<-
  hedge_sd<-
  vector( mode = 'numeric', length = nSize )
  
  gdp_gdp<-
  c_gdp<-
  i_gdp<-
  gov_gdp<-
  imp_gdp<-
  x_gdp<-
  nx_gdp<-
  p_gdp<-
  k_gdp<-
  inve_gdp<-
  emp_gdp<-
  profits_gdp<-
  wage_gdp<-
  prod_gdp<-
  mk_gdp<-
  kl_gdp<-
  infla_gdp<-
  u_gdp<-
  psh_gdp<-
  wsh_gdp<-
  pcu_gdp<-
  pr_gdp<-
  cgdp_gdp<-
  igdp_gdp<-
  ggdp_gdp<-
  nxgdp_gdp<-
  invgdp_gdp<-
  kgdp_gdp<-
  debtfs_gdp<-
  debtfs_st_gdp<-
  debtfs_lt_gdp<-
  depfs_gdp<-
  drt_fi_gdp<-
  drt_cl_gdp<-
  fshhi_gdp<-
  fslev_gdp<-
  fsstr_gdp<-
  fspr_gdp<-
  fsdr_gdp<-
  fsdef_gdp<-
  ponzi_gdp<-
  spec_gdp<-
  hedge_gdp<-
  rescue_gdp<-
  cpi_gdp<-
    ir_gdp<-
    debt_debt<-
    drt_fi_debt<-
    drt_cl_debt<-
    fshhi_debt<-
    fslev_debt<-
    fsstr_debt<-
    fspr_debt<-
    fsdr_debt<-
    fsdef_debt<-
    ponzi_debt<-
    spec_debt<-
    hedge_debt<-
    rescue_debt<-
    ir_debt<-
    inv_inv<-
    drt_fi_inv<-
    drt_cl_inv<-
    fshhi_inv<-
    fslev_inv<-
    fsstr_inv<-
    fspr_inv<-
    fsdr_inv<-
    fsdef_inv<-
    ponzi_inv<-
    spec_inv<-
    hedge_inv<-
    rescue_inv<-
    ir_inv<-
    ir_ir<-
    gdp_ir<-
    p_ir<-
    psh_ir<-
    wsh_ir<- 
    pcu_ir<-
    drt_fi_ir<-
    drt_cl_ir<-
    infla_ir<-
    cpi_ir<-
  list( )
  
  gdp_gdp_pval<- 
  cr_gdp_pval<- 
  ir_gdp_pval<- 
  gov_gdp_pval<- 
  imp_gdp_pval<- 
  x_gdp_pval<- 
  nx_gdp_pval<- 
  p_gdp_pval<- 
  k_gdp_pval<- 
  inve_gdp_pval<- 
  emp_gdp_pval<- 
  wage_gdp_pval<- 
  profits_gdp_pval<- 
  wage_gdp_pval<- 
  prod_gdp_pval<- 
  mk_gdp_pval<- 
  kl_gdp_pval<- 
  infla_gdp_pval<- 
  u_gdp_pval<- 
  pr_sh_gdp_pval<- 
  wg_sh_gdp_pval<- 
  pcu_gdp_pval<- 
  pr_gdp_pval<- 
  cgdp_gdp_pval<- 
  igdp_gdp_pval<- 
  ggdp_gdp_pval<- 
  nxgdp_gdp_pval<- 
  invgdp_gdp_pval<- 
  kgdp_gdp_pval<- 
  debtfs_gdp_pval<-
  debtfs_st_gdp_pval<-
  debtfs_lt_gdp_pval<-
  depfs_gdp_pval<-
  drt_fi_gdp_pval<-
  drt_cl_gdp_pval<-
  fshhi_gdp_pval<-
  fslev_gdp_pval<-
  fsstr_gdp_pval<-
  fspr_gdp_pval<-
  fsdr_gdp_pval<-
  ponzi_gdp_pval<-
  spec_gdp_pval<-
  hedge_gdp_pval<-
  vector( mode = "numeric", length = nExp )
  
 adf_gdp_growth<-
 adf_capacity_utilization<-
 adf_crisis<-
 adf_inflation<-
 adf_inflation_cpi<-
 adf_exchange_rate<-
 adf_reserves_ratio<-
 adf_primary_surplus_ratio<-
 adf_pubic_debt_ratio<-
 adf_profit_rate<-
 adf_profit_share<-
 adf_wage_share<-
 adf_debt_rate_firms<-
 adf_debt_rate_class<-
 adf_ponzi_rate<-
 adf_speculative_rate<-
 adf_hedge_rate<-
 adf_financial_demand_met<-
 adf_bankrupt_rate<-
 adf_consumption_gdp<-
 adf_investment_gdp<-
 adf_government_gdp<-
 adf_netexports_gdp<-
 adf_inventories_gdp<-
 adf_capital_gdp<-
 list( )
  
  # ====== FOR EACH EXPERIMENT ======
  
  for(k in 1 : nExp){ # Experiment k
    
    # ==== Filtered Plots ======
    
    plot_bpf( list( log0( Adata[[ k ]]$Country_GDP ), log0( Adata[[ k ]]$C ), 
                    log0( Adata[[ k ]]$I ) ),
              pl = lowP, pu = highP, nfix = bpfK, mask = TmaskPlot,
              mrk = transMk, # uncomment to add vertical line in selected point (e.g. mark of regime change)
              col = colors, lty = lTypes,
              leg = c( "GDP", "Consumption", "Investment" ),
              xlab = "Time", ylab = "Filtered series",
              tit = paste( "GDP cycles (", legends[ k ], ")" ),
              subtit = paste( "( Baxter-King bandpass-filtered, low = 6Q / high = 32Q / order = 12 / MC runs =",
                              nSize, ")" ) )
    
    plot_bpf( list( log0( Adata[[ k ]]$Country_GDP ), ( Adata[[ k ]]$IR )),
              pl = lowP, pu = highP, nfix = bpfK, mask = TmaskPlot,
              mrk = transMk, # uncomment to add vertical line in selected point (e.g. mark of regime change)
              col = colors, lty = lTypes,
              leg = c( "GDP", "Basic Interest Rate" ),
              xlab = "Time", ylab = "Filtered series",
              tit = paste( "GDP cycles (", legends[ k ], ")" ),
              subtit = paste( "( Baxter-King bandpass-filtered, low = 6Q / high = 32Q / order = 12 / MC runs =",
                              nSize, ")" ) )
    
 
    
    # ==== Statistics computation for tables ====
    
    for( j in 1 : nSize ){  # Execute for every Monte Carlo run
      
      # Monte carlo average growth rates and shares
        gdp_growth [ j ]<- mcData[[ k ]][ nTstat, "GDP_G", j ]
        capacity_utilization [ j ]<- mcData[[ k ]][ nTstat, "PCU", j ]
        crisis [ j ]<- mcData[[ k ]][ nTstat, "Cri", j ]
        inflation [ j ]<- mcData[[ k ]][ nTstat, "P_G", j ]
        inflation_cpi [ j ]<- mcData[[ k ]][ nTstat, "CPI_G", j ] 
        exchange_rate [ j ]<- mcData[[ k ]][ nTstat, "ER", j ]
        reserves_ratio [ j ]<- mcData[[ k ]][ nTstat, "RES_GDP", j ]
        primary_surplus_ratio [ j ]<- mcData[[ k ]][ nTstat, "PS_GDP", j ]
        pubic_debt_ratio [ j ]<- mcData[[ k ]][ nTstat, "PDEBT_GDP", j ]
        profit_rate [ j ]<- mcData[[ k ]][ nTstat, "PR", j ]
        profit_share [ j ]<- mcData[[ k ]][ nTstat, "PSH", j ] 
        wage_share [ j ]<- mcData[[ k ]][ nTstat, "WSH", j ] 
        debt_rate_firms [ j ]<- mcData[[ k ]][ nTstat, "DEBT_RT_FI", j ]
        debt_rate_class [ j ]<- mcData[[ k ]][ nTstat, "DEBT_RT_CL", j ]
        ponzi_rate [ j ]<- mcData[[ k ]][ nTstat, "PONZI", j ]
        speculative_rate [ j ]<- mcData[[ k ]][ nTstat, "SPEC", j ] 
        hedge_rate [ j ]<- mcData[[ k ]][ nTstat, "HEDGE", j ]
        financial_demand_met [ j ]<- mcData[[ k ]][ nTstat, "FS_DMET", j ]
        bankrupt_rate [ j ]<- mcData[[ k ]][ nTstat, "BKR_RT", j ]
        consumption_gdp [ j ]<- mcData[[ k ]][ nTstat, "CGDP", j ]
        investment_gdp [ j ]<- mcData[[ k ]][ nTstat, "IGDP", j ]
        government_gdp [ j ]<- mcData[[ k ]][ nTstat, "GGDP", j ] 
        netexports_gdp [ j ]<- mcData[[ k ]][ nTstat, "NXGDP", j ]
        inventories_gdp [ j ]<- mcData[[ k ]][ nTstat, "INVGDP", j ] 
        capital_gdp [ j ]<- mcData[[ k ]][ nTstat, "KGDP", j ]

      # Augmented Dickey-Fuller tests for unit roots
        adf_gdp_growth [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "GDP_G", j ] )
          adf_capacity_utilization [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PCU", j ] )
          adf_crisis [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "Cri", j ] )
          adf_inflation [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "P_G", j ] )
          adf_inflation_cpi [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "CPI_G", j ] )
          adf_exchange_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "ER", j ] )
          adf_reserves_ratio [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "RES_GDP", j ] )
          adf_primary_surplus_ratio [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PS_GDP", j ] )
          adf_pubic_debt_ratio [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PDEBT_GDP", j ] )
          adf_profit_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PR", j ] )
          adf_profit_share [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PSH", j ] )
          adf_wage_share [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "WSH", j ] )
          adf_debt_rate_firms [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "DEBT_RT_FI", j ] )
          adf_debt_rate_class [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "DEBT_RT_CL", j ] )
          adf_ponzi_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "PONZI", j ] )
          adf_speculative_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "SPEC", j ] )
          adf_hedge_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "HEDGE", j ] )
          adf_financial_demand_met [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "FS_DMET", j ] )
          adf_bankrupt_rate [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "BKR_RT", j ] )
          adf_consumption_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "CGDP", j ] )
          adf_investment_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "IGDP", j ] )
          adf_government_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "GGDP", j ] )
          adf_netexports_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "NXGDP", j ] )
          adf_inventories_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "INVGDP", j ] )
          adf_capital_gdp [[ j ]]<- adf.test( mcData[[ k ]][ TmaskStat, "KGDP", j ] )
     
      # Apply Baxter-King filter to the series
      gdp_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "Country_GDP", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      c_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "C", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      i_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "I", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      g_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "G", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      m_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "M", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      x_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "X", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      nx_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "NX", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      p_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "P", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      pr_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "PROFITS", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      wg_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "WAGE", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      wsh_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "WSH", j ] , pl = lowP, pu = highP, nfix = bpfK )
      psh_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "PSH", j ] , pl = lowP, pu = highP, nfix = bpfK )
      mk_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "MK", j ] , pl = lowP, pu = highP, nfix = bpfK )
      pr_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "PR", j ] , pl = lowP, pu = highP, nfix = bpfK )
      prod_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "PROD", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      pcu_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "PCU", j ] , pl = lowP, pu = highP, nfix = bpfK )
      inve_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "INVE_r", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      k_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "K_r", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      emp_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "EMP", j ] ), pl = lowP, pu = highP, nfix = bpfK )
    
      debtfs_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "DEBT_FS", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      debtfs_st_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "DEBT_FS_ST", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      debtfs_lt_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "DEBT_FS_LT", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      depfs_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "DEP_FS", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      drt_fi_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "DEBT_RT_FI", j ] , pl = lowP, pu = highP, nfix = bpfK )
      drt_cl_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "DEBT_RT_CL", j ] , pl = lowP, pu = highP, nfix = bpfK )
      fslev_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "FS_LEV", j ] , pl = lowP, pu = highP, nfix = bpfK )
      fsdr_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "FS_DR", j ] , pl = lowP, pu = highP, nfix = bpfK )
      fspr_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "FS_PR", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      fsdef_bpf<- bkfilter( log0( mcData[[ k ]][ TmaskStat, "FS_DEF", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      ponzi_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "PONZI", j ] , pl = lowP, pu = highP, nfix = bpfK )
      spec_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "SPEC", j ] , pl = lowP, pu = highP, nfix = bpfK )
      hedge_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "HEDGE", j ] , pl = lowP, pu = highP, nfix = bpfK )
      rescue_bpf<- bkfilter( log0(mcData[[ k ]][ TmaskStat, "RES", j ] ), pl = lowP, pu = highP, nfix = bpfK )
      cpi_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "CPI_G", j ] , pl = lowP, pu = highP, nfix = bpfK )
      infla_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "P_G", j ] , pl = lowP, pu = highP, nfix = bpfK )
      ir_bpf<- bkfilter( mcData[[ k ]][ TmaskStat, "IR", j ] , pl = lowP, pu = highP, nfix = bpfK )
      
      # Standard deviations of filtered series
      gdp_bpf_sd[ j ]<- sd( gdp_bpf$cycle[ TmaskBpf, 1 ] )
      c_bpf_sd[ j ]<- sd( c_bpf$cycle[ TmaskBpf, 1 ] )
      i_bpf_sd[ j ]<- sd( i_bpf$cycle[ TmaskBpf, 1 ] )
      g_bpf_sd[ j ]<- sd( g_bpf$cycle[ TmaskBpf, 1 ] )
      m_bpf_sd[ j ]<- sd( m_bpf$cycle[ TmaskBpf, 1 ] )
      x_bpf_sd[ j ]<- sd( x_bpf$cycle[ TmaskBpf, 1 ] )
      nx_bpf_sd[ j ]<- sd( nx_bpf$cycle[ TmaskBpf, 1 ] )
      p_bpf_sd[ j ]<- sd( p_bpf$cycle[ TmaskBpf, 1 ] )
      pr_bpf_sd[ j ]<- sd( pr_bpf$cycle[ TmaskBpf, 1 ] )
      wg_bpf_sd[ j ]<- sd( wg_bpf$cycle[ TmaskBpf, 1 ] )
      emp_bpf_sd[ j ]<- sd( emp_bpf$cycle[ TmaskBpf, 1 ] )
      pcu_bpf_sd[ j ]<- sd( pcu_bpf$cycle[ TmaskBpf, 1 ] )
      dr_bpf_sd[ j ]<- sd( drt_fi_bpf$cycle[ TmaskBpf, 1 ] )
      lev_bpf_sd[ j ]<- sd( fslev_bpf$cycle[ TmaskBpf, 1 ] )
      ir_bpf_sd[ j ]<- sd( ir_bpf$cycle[ TmaskBpf, 1 ] )
      
      # Build the correlation structures
      gdp_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ],gdp_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      c_gdp[[ j ]] <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], c_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      i_gdp[[ j ]] <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], i_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      gov_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ], g_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      imp_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ], m_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      x_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ], x_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      nx_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ], nx_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      p_gdp[[ j ]] <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], p_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      profits_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ], pr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      wage_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],wg_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      wsh_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],wsh_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      psh_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],psh_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      mk_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],mk_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      pr_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],pr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      prod_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],prod_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      pcu_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],pcu_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      inve_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],inve_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      k_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],k_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      emp_gdp[[ j ]] <- ccf(gdp_bpf$cycle[ TmaskBpf, 1 ],emp_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      debtfs_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], debtfs_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      debtfs_st_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], debtfs_st_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      debtfs_lt_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], debtfs_lt_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      depfs_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], depfs_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_fi_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], drt_fi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_cl_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], drt_cl_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fslev_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], fslev_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fspr_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], fspr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdr_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], fsdr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdef_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], fsdef_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ponzi_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], ponzi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      spec_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], spec_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      hedge_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], hedge_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      rescue_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], rescue_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      infla_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], infla_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      cpi_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], cpi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ir_gdp[[ j ]]  <- ccf( gdp_bpf$cycle[ TmaskBpf, 1 ], ir_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      
      
      debt_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], debtfs_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_fi_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], drt_fi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_cl_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], drt_cl_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fslev_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], fslev_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fspr_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], fspr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdr_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], fsdr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdef_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], fsdef_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ponzi_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], ponzi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      spec_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], spec_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      hedge_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], hedge_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      rescue_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], rescue_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ir_debt[[ j ]]  <- ccf( debtfs_bpf$cycle[ TmaskBpf, 1 ], ir_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      
      inv_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], i_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_fi_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], drt_fi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_cl_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], drt_cl_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fslev_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], fslev_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fspr_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], fspr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdr_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], fsdr_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      fsdef_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], fsdef_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ponzi_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], ponzi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      spec_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], spec_bpf$cycle[ TmaskBpf, 1 ],  lag.max = lags, plot = FALSE, na.action = na.pass )
      hedge_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], hedge_bpf$cycle[ TmaskBpf, 1 ],lag.max = lags, plot = FALSE, na.action = na.pass )
      rescue_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], rescue_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      ir_inv[[ j ]]  <- ccf( i_bpf$cycle[ TmaskBpf, 1 ], ir_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      
      ir_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], ir_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      gdp_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], gdp_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      p_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], p_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      psh_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], psh_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      wsh_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], wsh_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      pcu_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], pcu_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_fi_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], drt_fi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      drt_cl_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], drt_cl_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      infla_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], infla_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      cpi_ir[[ j ]]  <- ccf( ir_bpf$cycle[ TmaskBpf, 1 ], cpi_bpf$cycle[ TmaskBpf, 1 ], lag.max = lags, plot = FALSE, na.action = na.pass )
      
      }
    
    # Applies t test to the mean lag results to test their significance (H0: lag < critCorr)
    for(i in 1 : (2 * lags + 1) ){ #do for all lags
      if(i != lags + 1)  # don't try to compute autocorrelation at lag 0
      gdp_gdp_pval[ i ]<- t.test0( abs( unname( sapply( gdp_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      cr_gdp_pval[ i ]<- t.test0( abs( unname( sapply( c_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      ir_gdp_pval[ i ]<- t.test0( abs( unname( sapply( i_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      gov_gdp_pval[ i ]<- t.test0( abs( unname( sapply( gov_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      imp_gdp_pval[ i ]<- t.test0( abs( unname( sapply( imp_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      x_gdp_pval[ i ]<- t.test0( abs( unname( sapply( x_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      nx_gdp_pval[ i ]<- t.test0( abs( unname( sapply( nx_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      p_gdp_pval[ i ]<- t.test0( abs( unname( sapply( p_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      profits_gdp_pval[ i ]<- t.test0( abs( unname( sapply( profits_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      wage_gdp_pval[ i ]<- t.test0( abs( unname( sapply( wage_gdp, `[[`, "acf" ) )[ i, ] ), critCorr, CI )
      
    }
    
    #
    # ==== Summary statistics table ====
    
    key.stats <- matrix(
      c(
        ## avg. growth rate
        mean( gdp_growth ), 
        mean( capacity_utilization ),
        mean( crisis ),
        mean( inflation ), 
        mean( inflation_cpi ), 
        mean( exchange_rate ),
        mean( reserves_ratio ),
        mean( primary_surplus_ratio ),
        mean( pubic_debt_ratio ),
        mean( profit_rate ),
        mean( profit_share ), 
        mean( wage_share ), 
        mean( debt_rate_firms ),
        mean( debt_rate_class ),
        mean( ponzi_rate  ), 
        mean( speculative_rate  ), 
        mean( hedge_rate  ),
        mean( financial_demand_met ),
        mean( bankrupt_rate ),
        mean( consumption_gdp ),
        mean( investment_gdp ),
        mean( government_gdp ), 
        mean( netexports_gdp ),
        mean( inventories_gdp ), 
        mean( capital_gdp ),
        
        ## (Std. Dev.)
        sd( gdp_growth ), 
        sd( capacity_utilization ),
        sd( crisis ),
        sd( inflation ), 
        sd( inflation_cpi ), 
        sd( exchange_rate ),
        sd( reserves_ratio ),
        sd( primary_surplus_ratio ),
        sd( pubic_debt_ratio ),
        sd( profit_rate ),
        sd( profit_share ), 
        sd( wage_share ), 
        sd( debt_rate_firms ),
        sd( debt_rate_class ),
        sd( ponzi_rate  ), 
        sd( speculative_rate  ), 
        sd( hedge_rate  ),
        sd( financial_demand_met ),
        sd( bankrupt_rate ),
        sd( consumption_gdp ),
        sd( investment_gdp ),
        sd( government_gdp ), 
        sd( netexports_gdp ),
        sd( inventories_gdp ), 
        sd( capital_gdp ),
        
        ## ADF test (logs)
        mean( unname( sapply( adf_gdp_growth , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_capacity_utilization , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_crisis , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_inflation , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_inflation_cpi , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_exchange_rate , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_reserves_ratio , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_primary_surplus_ratio , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_pubic_debt_ratio , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_profit_rate , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_profit_share , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_wage_share , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_debt_rate_firms  , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_debt_rate_class , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_ponzi_rate  , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_speculative_rate  , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_hedge_rate  , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_financial_demand_met, `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_bankrupt_rate   , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_consumption_gdp , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_investment_gdp   , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_government_gdp   , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_netexports_gdp   , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_inventories_gdp , `[[`, "statistic" ) ) ),
        mean( unname( sapply( adf_capital_gdp  , `[[`, "statistic" ) ) ),
        
        ## ADF test (logs) p.value
        mean( unname( sapply( adf_gdp_growth , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_capacity_utilization , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_crisis , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_inflation , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_inflation_cpi , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_exchange_rate , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_reserves_ratio , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_primary_surplus_ratio , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_pubic_debt_ratio , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_profit_rate , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_profit_share , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_wage_share , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_debt_rate_firms  , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_debt_rate_class , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_ponzi_rate  , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_speculative_rate  , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_hedge_rate  , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_financial_demand_met, `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_bankrupt_rate   , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_consumption_gdp , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_investment_gdp   , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_government_gdp   , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_netexports_gdp   , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_inventories_gdp , `[[`, "p.value" ) ) ),
        mean( unname( sapply( adf_capital_gdp  , `[[`, "p.value" ) ) )
      ),
      ncol = 4, byrow = F)
    
    rownames( key.stats ) <- c(   "Real GDP Growth", 
                                  "Capacity Utilization", 
                                  "Probability of Crisis",
                                  "Inflation",
                                  "CPI Inflation",
                                  "Exchange Rate",
                                  "Reserves/GDP Ratio",
                                  "Primary Surplus/GDP Ratio", 
                                  "Public Debt/GDP Ratio",
                                  "Profit Rate",
                                  "Profit Share",
                                  "Wage Share",
                                  "Avg. Firms Debt Rate",
                                  "Avg. Class Debt Rate",
                                  "Share of Ponzi Firms",
                                  "Share of Speculative Firms", 
                                  "Share of Hedge Firms",
                                  "Credit Rationing",
                                  "Bankrupt Rate",
                                  "Consumption Share of GDP",
                                  "Investment Share of GDP",
                                  "Government Share of GDP",
                                  "Net Exports Share of GDP",
                                  "Inventories Share of GDP",
                                  "Capital Stock Share of GDP"
                                  )
    
    colnames( key.stats ) <- c(   "Avg. Rate",
                                  "Std. Dev.",
                                  "ADF test (logs)",
                                  "ADF p-val" )
    
    textplot( formatC( key.stats, digits = sDigits, format = "g" ), cmar = 2 )
    title <- paste( "Key statistics and unit roots tests (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote(paste0( "( bpf: Baxter-King bandpass-filtered series, low = ", .( lowP ),
                                            "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                            " / MC runs = ", .( nSize ), " / period = ",
                                            .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ),
                       eval( bquote( paste0( "( ADF test H0: there are unit roots / non-stationary at ",
                                             .( (1 - CI ) * 100), "% level", " )" ) ) ), sep ="\n" )
    title( main = title, sub = subTitle )
    
    # Write tables to the disk as CSV files for Excel
    write.csv( key.stats , quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_key_stats.csv" ) )
    
    # ==== Filtered statistics table ====
    bpf.stats <- matrix(
      c(
        ## S.d. of bpf series
        mean( gdp_bpf_sd ), 
        mean( c_bpf_sd ), 
        mean( i_bpf_sd ),
        mean( g_bpf_sd ), 
        mean( m_bpf_sd ), 
        mean( x_bpf_sd ), 
        mean( nx_bpf_sd ), 
        mean( p_bpf_sd ),
        mean( pr_bpf_sd ), 
        mean( wg_bpf_sd ),
        mean( emp_bpf_sd ),
        mean( pcu_bpf_sd ),
        mean( dr_bpf_sd ),
        mean( lev_bpf_sd ),
        mean( ir_bpf_sd ),
        
        ## relative s.d. (to GDP)
        1, 
        mean( c_bpf_sd ) / mean( gdp_bpf_sd ), 
        mean( i_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( g_bpf_sd ) / mean( gdp_bpf_sd ), 
        mean( m_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( x_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( nx_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( p_bpf_sd ) / mean( gdp_bpf_sd ), 
        mean( pr_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( wg_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( emp_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( pcu_bpf_sd ) / mean( gdp_bpf_sd ), 
        mean( dr_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( lev_bpf_sd ) / mean( gdp_bpf_sd ),
        mean( ir_bpf_sd ) / mean( gdp_bpf_sd )
        
      ),
      ncol = 2, byrow = F)
    
    rownames( bpf.stats ) <- c( "GDP (output)", 
                                "Consumption", 
                                "Investment", 
                                "Gov. Expend.",
                                "Imports",
                                "Exports",
                                "Net Exports",
                                "Prices", 
                                "Profit", 
                                "Wages",
                                "Employment",
                                "Capacity Utilization",
                                "Firms' Debt Rate",
                                "Banks' Leverage",
                                "Basic Interest Rate"
    )
    
    colnames( bpf.stats ) <- c(   " s.d. (bpf)", 
                                  " s.d. relative to GDP" )
    
    textplot( formatC( bpf.stats, digits = sDigits, format = "g" ), cmar = 2 )
    title <- paste( "Filtered statistics for cycles (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote(paste0( "( bpf: Baxter-King bandpass-filtered series, low = ", .( lowP ),
                                            "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                            " / MC runs = ", .( nSize ), " / period = ",
                                            .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ) )
    title( main = title, sub = subTitle )
    
    # Write tables to the disk as CSV files for Excel
    write.csv( bpf.stats , quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_bpf_stats.csv" ) )
   
    
    #
    # ==== Correlation structure tables (lags, standard errors and p-values) ====
    corr.struct.gdp <- matrix(c(  colMeans(t( unname( sapply(gdp_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(c_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(i_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(gov_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(imp_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(x_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(nx_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(p_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(profits_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(wage_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(psh_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(wsh_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(mk_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(pr_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(prod_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(pcu_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(inve_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(k_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(emp_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(debtfs_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(debtfs_st_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(debtfs_lt_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(depfs_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(drt_fi_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(drt_cl_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(fslev_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(fspr_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(fsdr_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(fsdef_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(ponzi_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(spec_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(hedge_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(rescue_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(infla_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(cpi_gdp, `[[`, "acf" ) ) ), na.rm = T),
                                  colMeans(t( unname( sapply(ir_gdp, `[[`, "acf" ) ) ), na.rm = T)
                              
                            ),
    
    ncol = 2 * lags + 1, byrow = T)
    colnames( corr.struct.gdp ) <- gdp_gdp[[1]]$lag
    rownames( corr.struct.gdp ) <- c(   "GDP (output)",
                                    "Consumption", 
                                    "Investment",
                                    "Gov. Expenditure",
                                    "Imports",
                                    "Exports", 
                                    "Net Exports", 
                                    "Price",
                                    "Profits", 
                                    "Wages",
                                    "Profit Shate", 
                                    "Wage Share",
                                    "Markup",
                                    "Profit Rate",
                                    "Productivity",
                                    "Capacity Utilization",
                                    "Stock of Inventories",
                                    "Stock of Capital",
                                    "Employment",
                                    "Total Debt",
                                    "Short Term Loans", 
                                    "Long Term Loans", 
                                    "Total Deposits", 
                                    "Firms Debt Rate", 
                                    "Class Debt Rate", 
                                    "Financial Sector Leverage",
                                    "Financial Sector Profits", 
                                    "Financial Sector Default Rate",
                                    "Defaulted Loans",
                                    "Share of Ponzi Firms", 
                                    "Share of Speculative Firms", 
                                    "Share of Hedge Firms",
                                    "Bank Rescue",
                                    "Inflation",
                                    "CPI Inflation",
                                    "Basic Interest Rate"
    )
    
    textplot( formatC( corr.struct.gdp, digits = sDigits, format = "g" ), cmar = 1 )
    title <- paste( "Correlation structure for GDP (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote( paste0( "( non-rate/ratio series are Baxter-King bandpass-filtered, low = ",
                                             .( lowP ), "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                             " / MC runs = ", .( nSize ), " / period = ",
                                             .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ),
                       eval( bquote ( paste0( "( test H0: lag coefficient is not significant at ",
                                              .( ( 1 - CI ) * 100), "% level", " )" ) ) ), sep ="\n" )
    title( main = title, sub = subTitle )
    write.csv( corr.struct.gdp, quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_corr_struct_gdp.csv" ) )
    
    
    corr.struct.debt <- matrix(c( colMeans(t( unname( sapply(drt_fi_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(drt_cl_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(fslev_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(fspr_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(fsdr_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(fsdef_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(ponzi_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(spec_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(hedge_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(rescue_debt, `[[`, "acf" ) ) ), na.rm = T),
                                 colMeans(t( unname( sapply(ir_debt, `[[`, "acf" ) ) ), na.rm = T)
    ),
    
    ncol = 2 * lags + 1, byrow = T)
    colnames( corr.struct.debt ) <- debt_debt[[1]]$lag
    rownames( corr.struct.debt ) <- c( "Firms Debt Rate", 
                                    "Class Debt Rate", 
                                    "Financial Sector Leverage",
                                    "Financial Sector Profits", 
                                    "Financial Sector Default Rate",
                                    "Defaulted Loans",
                                    "Share of Ponzi Firms", 
                                    "Share of Speculative Firms", 
                                    "Share of Hedge Firms",
                                    "Bank Rescue",
                                    "Basic Interest Rate"
    )
    
    textplot( formatC( corr.struct.debt, digits = sDigits, format = "g" ), cmar = 1 )
    title <- paste( "Correlation structure for Stock of Credit (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote( paste0( "( non-rate/ratio series are Baxter-King bandpass-filtered, low = ",
                                             .( lowP ), "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                             " / MC runs = ", .( nSize ), " / period = ",
                                             .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ),
                       eval( bquote ( paste0( "( test H0: lag coefficient is not significant at ",
                                              .( ( 1 - CI ) * 100), "% level", " )" ) ) ), sep ="\n" )
    title( main = title, sub = subTitle )
    write.csv( corr.struct.debt, quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_corr_struct_debt.csv" ) )
    
    
    corr.struct.interest <-  matrix(c( colMeans(t( unname( sapply(ir_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(gdp_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(p_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(psh_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(wsh_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(pcu_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(drt_fi_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(drt_cl_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(infla_ir, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(cpi_ir, `[[`, "acf" ) ) ), na.rm = T)
                                     
    ),
    
    ncol = 2 * lags + 1, byrow = T)
    colnames( corr.struct.interest ) <- ir_ir[[1]]$lag
    rownames( corr.struct.interest ) <- c( "Basic Interest Rate", 
                                          "GDP", 
                                          "Prices",
                                          "Profit Share", 
                                          "Wage Share",
                                          "Capacity Utilization",
                                          "Firms' Debt Rate", 
                                          "Households' Debt Rate", 
                                          "Inflation",
                                          "CPI Inflation"
    )
    
    textplot( formatC( corr.struct.interest, digits = sDigits, format = "g" ), cmar = 1 )
    title <- paste( "Correlation structure for Basic Interest Rate (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote( paste0( "( non-rate/ratio series are Baxter-King bandpass-filtered, low = ",
                                             .( lowP ), "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                             " / MC runs = ", .( nSize ), " / period = ",
                                             .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ),
                       eval( bquote ( paste0( "( test H0: lag coefficient is not significant at ",
                                              .( ( 1 - CI ) * 100), "% level", " )" ) ) ), sep ="\n" )
    title( main = title, sub = subTitle )
    write.csv( corr.struct.interest, quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_corr_struct_interest.csv" ) )
    
    
    corr.struct.invest <-  matrix(c( colMeans(t( unname( sapply(drt_fi_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(drt_cl_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(fslev_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(fspr_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(fsdr_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(fsdef_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(ponzi_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(spec_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(hedge_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(rescue_inv, `[[`, "acf" ) ) ), na.rm = T),
                                     colMeans(t( unname( sapply(ir_inv, `[[`, "acf" ) ) ), na.rm = T)
    ),
    
    ncol = 2 * lags + 1, byrow = T)
    colnames( corr.struct.invest ) <- inv_inv[[1]]$lag
    rownames( corr.struct.invest ) <- c( "Firms Debt Rate", 
                                         "Class Debt Rate", 
                                         "Financial Sector Leverage",
                                         "Financial Sector Profits", 
                                         "Financial Sector Default Rate",
                                         "Defaulted_Loans",
                                         "Share of Ponzi Firms", 
                                         "Share of Speculative Firms", 
                                         "Share of Hedge Firms",
                                         "Bank Rescue",
                                         "Basic Interest Rate"
    )
    
    textplot( formatC( corr.struct.invest, digits = sDigits, format = "g" ), cmar = 1 )
    title <- paste( "Correlation structure for Investment (", legends[ k ], ")" )
    subTitle <- paste( eval( bquote( paste0( "( non-rate/ratio series are Baxter-King bandpass-filtered, low = ",
                                             .( lowP ), "Q / high = ", .( highP ), "Q / order = ", .( bpfK ),
                                             " / MC runs = ", .( nSize ), " / period = ",
                                             .( warmUpStat + 1 ), " - ", .( nTstat ), " )" ) ) ),
                       eval( bquote ( paste0( "( test H0: lag coefficient is not significant at ",
                                              .( ( 1 - CI ) * 100), "% level", " )" ) ) ), sep ="\n" )
    title( main = title, sub = subTitle )
    write.csv( corr.struct.invest, quote = FALSE,
               paste0( folder, "/", baseName, outDir, "/", repName, k, "_corr_struct_invest.csv" ) )
    
  
  }

cat( "\nDone...\n" )
}, interrupt = function( ex ) {
  cat( "An interrupt was detected.\n" )
  print( ex )
  textplot( "Report incomplete due to interrupt." )
}, error = function( ex ) {
  cat( "An error was detected.\n" )
  print( ex )
  textplot( "Report incomplete due to processing error." )
}, finally = {
  options( warn = 0 )
  cat( "\n", as.character( Sys.time( ) ), "-> Releasing resources...\n\n" )
  totalTime <- proc.time( ) - startTime
  print( totalTime )
  # Close PDF plot file
  dev.off( )
} )


