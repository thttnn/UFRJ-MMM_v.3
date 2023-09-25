/*************************************************************

	LSD 8.0 - May 2022
	written by Marco Valente, Universita' dell'Aquila
	and by Marcelo Pereira, University of Campinas

	Copyright Marco Valente and Marcelo Pereira
	LSD is distributed under the GNU General Public License

	See Readme.txt for copyright information of
	third parties' code used in LSD

 *************************************************************/

/*************************************************************
VARIAB.CPP
The (C++) object variable is devoted to contain numerical values
of the model. Only double precision floating point numbers are used
in LSD. Variables are mainly storages for information. Actually, all
the work is done by LSD objects.

The most important task of variables is to return their value when requested.
It is done by comparing the global time of the simulation with the time
the variable was most recently updated. If the value requested (considering the
lag ) is already available, that is returned. Otherwise, the variable shifts
its lagged values, and calls its equation to compute the new value.

All fields and functions in variables are public, so that users may override
the default mechanism.

The fields composing a variables are

- char *label;
name of the variable. It needs to be unique in the model

- object *up;
address of the object containing the variable

- variable *next;
pointer to the next variable contained in the object. Variables in an object
are organized as a linked chain, and can be reached only  via their fields
next

- double *val;
vector of numerical values. val[ 0 ] is the most recent value computed by the
equation, that is, computed at time last_update. val[1] is the value computed
at time last_update - 1; val[2] at time last_update - 2 and so on.

- int num_lag;
number of lagged values stored for the variable

- int save;
flag identifying whether the variable has to be saved or not in the result file

- int plot;
Flag used to indicate variables that are plotted in the run time graph.

- char deb_mode;
flag used to indicate the variables to debug. If this flag is equal 'd', when the
simulation is run in debug mode it stops immediately after the computation of
its value.

- int deb_cond;
Like the flag deb_mode, but it stops the simulation if the attached condition is
satisfied. It does not require that the simulation is run in debug mode.
Its different values represent the different conditions for stopping: <, > or ==

- double deb_cnd_val;
numerical value used for the conditional stop

- int under_computation;
control flag used to avoid infinite recursion of an equation calling itself.
Used to issue a message of error

- int last_update;
contain the global time when it was lastly computed the equation for the variable

- int param;
Flag set to 1, in case the variable is considered a parameter. In case it is,
when requested the value it is always returned its field val[ 0 ].

- char data_loaded;
flag indicative whether the variable has been initialized with numerical values
set as default by the system or if they were actually chosen by the user.
The flag is 0 in case of newly created objects and 1 in case the variable's
values has been at least shown once in the initial values editor window.
This flag is also saved in the data file, so that this information is not lost.
The flag prevents to run a simulation if the data where not confirmed by users.

The main methods of the (C++) object variable are:

- void init( object *_up, char *_label, int _num_lag, double *val, int _save );
perform the initialization.

- double cal( object *caller, int lag );
it is its main function. Return the numerical value

	   val[last_update+lag-t]

if the condition

	   t-lag<=last_update

is satisfied. That means that either the variable has already been updated,
and therefore the requested value is available, or that, though the variable
has not been still updated in the time step, the value requested is a lagged one
and therefore can be retrived from the vector of the past values.

Only in case the lag requested is zero and the variable has not been computed
at the present time step, the method shifts its lagged values and calls the
method fun that perform the equation computation.

- void empty( void ) ;
It is used to free all the memory assigned to the variable. Used by
object::delete_obj to cancel an object.
*************************************************************/

#include "decl.h"

clock_t start_profile[ 100 ], end_profile[ 100 ];

#ifndef _NP_
condition_variable upd_workers;
mutex thr_ptr_lock;
mutex update_lock;
mutex crash_lock;
#endif


/****************************************************
VARIABLE
constructor
****************************************************/
variable::variable( void )
{
	dummy = false;
	observe = false;
	parallel = false;
	plot = false;
	save = false;
	savei = false;
	under_computation = false;
	lab_tit = NULL;
	label = NULL;
	data_loaded = '-';
	deb_mode = 'n';
	data = NULL;
	val = NULL;
	deb_cnd_val = 0;
	deb_cond = 0;
	end = 0;
	last_update = 0;
	next_update = 0;
	num_lag = 0;
	param = 0;
	start = 0;
	delay = 0;
	delay_range = 0;
	period = 1;
	period_range = 0;
	up = NULL;
	next = NULL;
	eq_func = NULL;
}


/****************************************************
VARIABLE
copy constructor
****************************************************/
variable::variable( const variable &v )
{
	dummy = v.dummy;
	observe = v.observe;
	parallel = v.parallel;
	plot = v.plot;
	save = v.save;
	savei = v.savei;
	under_computation = v.under_computation;
	lab_tit = v.lab_tit;
	label = v.label;
	data_loaded = v.data_loaded;
	deb_mode = v.deb_mode;
	data = v.data;
	val = v.val;
	deb_cnd_val = v.deb_cnd_val;
	deb_cond = v.deb_cond;
	end = v.end;
	last_update = v.last_update;
	next_update = v.next_update;
	num_lag = v.num_lag;
	param = v.param;
	start = v.start;
	delay = v.delay;
	delay_range = v.delay_range;
	period = v.period;
	period_range = v.period_range;
	up = v.up;
	next = v.next;
	eq_func = v.eq_func;
}


/****************************************************
INIT
****************************************************/
void variable::init( object *_up, const char *_label, int _num_lag, double *v, int _save )
{
	int i;

#ifndef _NP_
	// prevent concurrent use by more than one thread
	rec_lguardT lock( parallel_comp );
#endif

	up = _up;
	save = _save;

	i = strlen( _label ) + 1;
	label = new char[ i ];
	strcpy( label, _label );

	num_lag = _num_lag;
	if ( num_lag >= 0 )
	{
		val = new double[ num_lag + 1 ];
		for ( i = 0; i < num_lag + 1; ++i )
			val[ i ] = v[ i ];
	}
	else
		val = NULL;
}


/****************************************************
EMPTY
****************************************************/
void variable::empty( bool no_lock )
{

#ifndef _NP_

	if ( running && ! no_lock )
	{
		// prevent concurrent use by more than one thread
		rec_lguardT lock( parallel_comp );
	}

#endif

	if ( running && ( label == NULL || val == NULL ) )
	{
		error_hard( "internal problem in LSD",
					"if error persists, please contact developers",
					true,
					"failure while deallocating variable %s", label );
		return;
	}

	delete [ ] label;
	delete [ ] val;
	delete [ ] lab_tit;
	free( data );		// use C stdlib to be able to deallocate memory for deleted objects
}


/***************************************************
CAL
Standard version (non parallel computation)
****************************************************/
double variable::cal( object *caller, int lag )
{
	int i, eff_lag, time;
	clock_t pstart = 0, pend = 0;
	double app;

	if ( param == 1 )
	{
		if ( debug_flag && t == when_debug && ( deb_mode == 'w' || deb_mode == 'W' ) )
		{
			watch_trigger = true;
			watch_write_mode = false;
			strncpy( watch_elem, label, MAX_ELEM_LENGTH );
		}

		return val[ 0 ];				// it's a parameter, ignore lags
	}

#ifndef _NP_
	// prepare mutex for variables and functions updated in multiple threads
	rec_uniqlT guard( parallel_comp, defer_lock );
#endif

	if ( param == 0 )					// it's a variable
	{
		// invalid lag or value not saved yet
		if ( lag > num_lag && ( no_saved || ! ( save || savei ) || t - lag < start ) )
		{
			eff_lag = lag;
			goto error;
		}

		// effective lag for variables (compatible with older versions)
		eff_lag = ( last_update < t ) ? lag - 1 : lag;

		// check lag error and return past value if available
		if ( lag != 0 )
		{
			if ( eff_lag < 0 )			// with negative lag
				goto error;

			if ( eff_lag > num_lag )	// in principle, invalid lag
			{
				if ( no_saved || ! ( save || savei ) )	// and not saved
					goto error;
				else
					if ( lag > t - start )	// or before there are saved values
						goto error;

				return data[ t - lag - start ];	// use saved past value
			}
			else
				return val[ eff_lag ];	// use regular past value
		}
		else
		{
			// already calculated this time step or not to be calculated this time step
			if ( last_update >= t || t < next_update )
			{
				if ( debug_flag && t == when_debug && ( deb_mode == 'w' || deb_mode == 'W' ) )
				{
					watch_trigger = true;
					watch_write_mode = false;
					strncpy( watch_elem, label, MAX_ELEM_LENGTH );
				}

				return( val[ 0 ] );
			}
#ifndef _NP_
			// wait for computation of this variable by other threads
			if ( parallel_mode && ! dummy )
				guard.lock( );

			if ( last_update >= t )		// recheck if not computed during lock
				return( val[ 0 ] );
#endif
		}
	}
	else								// function
	{
		if ( lag < 0 || lag > num_lag )	// with invalid lag
			goto error;

		if ( lag > 0 )					// lagged value
			return val[ lag - 1 ];

		if ( caller == NULL )			// update or inadequate caller
			return val[ 0 ];

#ifndef _NP_
		// wait for computation of this function by other threads
		if ( parallel_mode && ! dummy )
			 guard.lock( );
#endif
	}

	// there is a value to be computed

	if ( under_computation )
	{
		error_hard( "deadlock",
					"check your equation code to prevent this situation\nprobably using the variable lagged value instead",
					true,
					"equation for '%s' (object '%s') requested \nits own value while computing its current value", label, up->label );
		return 0;
	}

	under_computation = true;

#ifndef _NP_
	if ( fast_mode == 0 && ! parallel_mode )
#else
	if ( fast_mode == 0 )
#endif
	{
		// add the Variable to the stack
		if ( stacklog != NULL && stacklog->next == NULL )
		{
			++stack;
			stacklog->next = new lsdstack;
			stacklog->next->next = NULL;
			stacklog->next->prev = stacklog;
			strcpyn( stacklog->next->label, label, MAX_ELEM_LENGTH );
			stacklog->next->ns = stack;
			stacklog->next->vs = this;
			stacklog = stacklog->next;
		}
		else
		{
			error_hard( "internal problem in LSD",
						"if error persists, please contact developers",
						true,
						"failure while pushing '%s' (object '%s')", label, up->label );
			return 0;
		}

#ifndef _NW_
		if ( stack_info >= stack && ( ! prof_obs_only || observe ) )
			start_profile[ stack - 1 ] = pstart = clock( );
		else
			if ( prof_aggr_time )
				pstart = clock( );
#endif
	}
#ifndef _NW_
	else
		if ( prof_aggr_time )
			pstart = clock( );
#endif

	// Compute the Variable's equation
	user_exception = true;			// allow distinguishing among internal & user exceptions
	try								// do it while catching exceptions to avoid obscure aborts
	{
		app = fun( caller );
	}
	catch ( exception& exc )
	{
		plog( "\n\nAn exception was detected while computing the equation \nfor '%s' requested by object '%s'", label, caller == NULL ? "(none)" : caller->label );
		quit = 2;
		throw;
	}
	catch ( int p )		// avoid general catch of error_hard() throwing to lsdmain()
	{
		throw p;
	}
	catch ( ... )
	{
		if ( quit != 2 )			// error message not already presented?
		{
			plog( "\n\nAn unknown problem was detected while computing the equation \nfor '%s' requested by object '%s'", label, caller == NULL ? "(none)" : caller->label );
			quit = 2;
			throw;
		}
		else
		{
			app = NAN;				// mark result as invalid
			use_nan = true;			// and allow propagation
		}
	}
	user_exception = false;

	for ( i = 0; i < num_lag; ++i ) // scale down the past values
		val[ num_lag - i ] = val[ num_lag - i - 1 ];

	val[ 0 ] = app;

	last_update = t;

	// choose next update step for special updating variables
	if ( period > 1 || period_range > 0 )
	{
		next_update = t + period;
		if ( period_range > 0 )
			next_update += rnd_int( 0, period_range );
	}

#ifndef _NP_
	if ( fast_mode == 0 && ! parallel_mode )
#else
	if ( fast_mode == 0 )
#endif
	{
#ifndef _NW_
		if ( prof_aggr_time )
		{
			pend = clock( );
			time = pend - pstart;

			if ( ( ! prof_obs_only || observe ) && time > prof_min_msecs )
			{
				string var_name = label;
				prof[ var_name ].ticks += time;
				prof[ var_name ].comp++;
			}
		}

		if ( stack_info >= stack && ( ! prof_obs_only || observe ) )
		{
			end_profile[ stack - 1 ] = prof_aggr_time ? pend : clock( );

			time = 1000 * ( end_profile[ stack - 1 ] - start_profile[ stack - 1 ] ) / CLOCKS_PER_SEC;

			if ( time >= prof_min_msecs )
			{
				set_lab_tit( this );
				plog_tag( "\n%-12.12s(%-.10s)\t=", "prof1", label, lab_tit );
				plog_tag( "%.4g\t", "highlight", val[ 0 ] );
				plog( "t=" );
				plog_tag( "%d\t", "highlight", t );
				plog( "msecs=" );
				plog_tag( "%d\t", "highlight", time );
				plog( "stack=" );
				plog_tag( "%d\t", "highlight", stack );
				plog( "caller=%s%s%s", caller == NULL ? "SYSTEM" : caller->label, caller == NULL ? "" : "\ttrigger=", caller == NULL || stacklog == NULL || stacklog->prev == NULL ? "" : stacklog->prev->label );
			}
		}

		// update debug log file
		if ( log_file != NULL && t >= log_start && t <= log_stop )
			fprintf( log_file, "%s\t= %g\t(t=%d)\n", label, val[ 0 ], t );

		// open the debugger if required
		if ( debug_flag && t == when_debug && ( watch_trigger || ( deb_cond == 0 && ( deb_mode == 'd' || deb_mode == 'W' || deb_mode == 'R' ) ) ) )
			deb( ( object * ) up, caller, label, &val[ 0 ], false );
		else
			switch ( deb_cond )
			{
				case 0:
					break;
				case 1:
					if ( val[ 0 ] == deb_cnd_val )
						deb( ( object * ) up, caller, label, &val[ 0 ], false );
					break;
				case 2:
					if ( val[ 0 ] > deb_cnd_val )
						deb( ( object * ) up, caller, label, &val[ 0 ], false );
					break;
				case 3:
					if ( val[ 0 ] < deb_cnd_val )
						deb( ( object * ) up, caller, label, &val[ 0 ], false );
					break;
				default:
					error_hard( "internal problem in LSD",
								"if error persists, please contact developers",
								true,
								"conditional debug '%d' in variable '%s'", deb_cond, label );
					return -1;
			}
#endif
		// remove the element from the stack
		if ( stacklog != NULL && stacklog->prev != NULL )
		{
			stacklog = stacklog->prev;
			delete stacklog->next;
			stacklog->next = NULL;
			stack--;
		}
		else
		{
			error_hard( "internal problem in LSD",
						"if error persists, please contact developers",
						true,
						"failure while poping '%s' (in object '%s')", label, up->label );
			return 0;
		}
	}

	under_computation = false;

	// if there is a pending deletion, try to do it now
	if ( wait_delete != NULL )
	{
#ifndef _NP_
		if ( guard.owns_lock( ) )
			guard.unlock( );					// release lock
#endif
		wait_delete->delete_obj( this );
	}

	return app;	// by default the requested value is the last one, not yet computed

	error:

	eff_lag = ( param == 0 ) ? eff_lag : lag;

	if ( eff_lag > 0 )
		error_hard( "invalid lag used",
					"check your configuration (variable max lag) or\ncode (used lags in equation) to prevent this situation",
					false,
					"variable or function '%s' (object '%s') requested \nwith lag=%d but declared with lag=%d\nPossible fixes:\n- change the model configuration, declaring '%s' with at least lag=%d,\n- change the code of '%s' requesting the value of '%s' with lag=%d maximum, or\n- enable USE_SAVED and mark '%s' to be saved (variables only)", label, up->label, eff_lag, num_lag, label, eff_lag, caller == NULL ? "(none)" : caller->label, label, num_lag, label );
	else
		error_hard( "invalid lag used",
					"check your code (used lags in equation) to prevent negative lag",
					false,
					"variable or function '%s' (object '%s') requested \nwith lag=%d but negative lags are not allowed here\nPossible fix: use positive lag instead", label, up->label, eff_lag );

	return 0;
}


#ifndef _NP_
/***************************************************
CAL_WORKER
Multi-thread worker for parallel computation
****************************************************/
void worker::cal_worker( void )
{
	int i;
	double app;

	// create try-catch block to capture exceptions in thread and reroute to main thread
	try
	{
		running = true;
		errored = false;

		// update object map and register all signal handlers
		unique_lock < mutex > lock_map( thr_ptr_lock );
		thr_id = this_thread::get_id( );
		thr_ptr[ thr_id ] = this;
		lock_map.unlock( );
		handle_signals( signal_wrapper );

		free = true;

		while ( running )
		{
			// wait for variable calculation message
			unique_lock < mutex > lock_worker( lock );
			run.wait( lock_worker, [ this ]{ return ! free; }  );

			// exit if shutdown or continue if already updated
			if ( running && var != NULL && var->last_update < t )
			{	// prevent parallel computation of the same variable
				rec_uniqlT guard_var( var->parallel_comp );

				// recheck if not computed during lock
				if ( var->last_update >= t )
					goto end;

				if ( var->under_computation )
				{
					snprintf( err_msg1, MAX_BUFF_SIZE, "deadlock during parallel computation" );
					snprintf( err_msg2, MAX_BUFF_SIZE, "the equation for '%s' in object '%s' requested its own value\nwhile parallel-computing its current value", var->label, var->up->label );
					snprintf( err_msg3, MAX_BUFF_SIZE, "check your code to prevent this situation" );
					user_excpt = true;

					if ( worker_errors( ) == 0 )
					{
						errored = true;
						throw;
					}
					else
					{
						errored = true;
						goto stop;
					}
				}

				var->under_computation = true;

				// compute the Variable's equation
				user_excpt = true;			// allow distinguishing among internal & user exceptions

#ifndef _NW_
				if ( setjmp( env ) )		// allow recovering from signals
					return;
#endif
				try							// do it while catching exceptions to avoid obscure aborts
				{
					app = var->fun( NULL );
				}
				catch ( ... )
				{
					if ( error_hard_thread )
						pexcpt = nullptr;
					else
					{
						pexcpt = current_exception( );
						snprintf( err_msg1, MAX_BUFF_SIZE, "equation error" );
						snprintf( err_msg2, MAX_BUFF_SIZE, "an exception was detected while parallel-computing the equation\nfor '%s' in object '%s'", var->label, var->up->label );
						snprintf( err_msg3, MAX_BUFF_SIZE, "check your code to prevent this situation" );
					}

					if ( worker_errors( ) == 0 )
					{
						errored = true;
						throw;
					}
					else
					{
						errored = true;
						goto stop;
					}
				}

				user_excpt = errored = false;

				// scale down the past values
				for ( i = 0; i < var->num_lag; ++i )
					var->val[ var->num_lag - i ] = var->val[ var->num_lag - i - 1 ];
				var->val[ 0 ] = app;

				var->last_update = t;

				// choose next update step for special updating variables
				if ( var->period > 1 || var->period_range > 0 )
				{
					var->next_update = t + var->period;
					if ( var->period_range > 0 )
						var->next_update += rnd_int( 0, var->period_range );
				}

				var->under_computation = false;

				// if there is a pending object deletion, try to do it now
				if ( wait_delete != NULL )
				{
					guard_var.unlock( );					// release lock
					wait_delete->delete_obj( var );
				}
			}

		end:
			var = NULL;
			free = true;
			// create context to send signal to update scheduler if needed
			if ( ! worker_ready )
			{
				unique_lock< mutex > lock_update( update_lock );
				// recheck if still needed
				if ( ! worker_ready )
				{
					worker_ready = true;
					upd_workers.notify_one( );
				}
			}
		}
	}
	catch ( ... )
	{
		// only capture exception if not already done
		if ( ! error_hard_thread && pexcpt != nullptr )
		{
			pexcpt = current_exception( );
			snprintf( err_msg1, MAX_BUFF_SIZE, "parallel computation problem" );
			snprintf( err_msg2, MAX_BUFF_SIZE, "an exception was detected while parallel-computing the equation\nfor '%s' in object '%s'", var->label, var->up->label );
			snprintf( err_msg3, MAX_BUFF_SIZE, "disable parallel computation for this variable\nor check your code to prevent this situation" );
		}
	}

	stop:

	running = free = false;
}


/***************************************************
WORKER constructor
****************************************************/
worker::worker( void )
{
	running = false;
	free = false;
	pexcpt = nullptr;
	signum = -1;
	var = NULL;
	strcpy( err_msg1, "" );
	strcpy( err_msg2, "" );
	strcpy( err_msg3, "" );

	// launch new thread (waiting mode)
	thr = thread( & worker::cal_worker, this );
}


/***************************************************
WORKER destructor
****************************************************/
worker::~worker( void )
{
	// command thread shutdown if running
	if ( running && ! errored )
	{
		unique_lock< mutex > lock_worker( lock );
		running = free = false;
		run.notify_one( );
	}

	// wait for shutdown and check exception
	if ( thr.joinable( ) && ! errored )
		thr.join( );

	// remove thread id from threads map
	thr_ptr.erase( thr_id );
}


/***************************************************
SIGNAL
Handle system signals in worker
****************************************************/
void worker::signal( int sig )
{
	char signame[ 16 ];

	switch ( sig )
	{
		case SIGMEM:
			strcpy( signame, "SIGMEM" );
			break;

		case SIGABRT:
			strcpy( signame, "SIGABRT" );
			break;

		case SIGFPE:
			strcpy( signame, "SIGFPE" );
			break;

		case SIGILL:
			strcpy( signame, "SIGILL" );
			break;

		case SIGSEGV:
			strcpy( signame, "SIGSEGV" );
			break;

		default:
			strcpy( signame, "Unknown signal" );
	}

	if ( var != NULL && var->label != NULL	)
		snprintf( err_msg1, MAX_BUFF_SIZE, "\n\n%s: signal received while parallel-computing the equation\nfor '%s' in object '%s'. Disable parallel computation for this variable\nor check your code to prevent this situation.", signame, var->label, var->up->label != NULL ? var->up->label : "(none)" );
	else
		snprintf( err_msg1, MAX_BUFF_SIZE, "\n\n%s: signal received by a parallel worker thread.\nDisable parallel computation to prevent this situation.", signame );

	// signal & kill thread
	signum = sig;
	free = false;
	running = false;

#ifndef _NW_
	longjmp( env, 1 );				// recover from crash on user code
#endif
}


/***************************************************
SIGNAL_WRAPPER
Reformat signal function format to comply with OS
****************************************************/
void worker::signal_wrapper( int signum )
{
	// pointer to the appropriate worker object
	worker *me = thr_ptr[ this_thread::get_id( ) ];

	// call member function
	me->signal( signum );
}


/***************************************************
CAL
Multi-thread CAL version (parallel computation)
****************************************************/
void worker::cal( variable *v )
{
	unique_lock< mutex > worker_lock( lock );
	var = v;
	free = false;
	run.notify_one( );
}


/****************************************************
CHECK
Check if worker is running and handle problems
****************************************************/
bool worker::check( void )
{
	if ( running && ! errored )				// nothing to do?
		return true;

	// only process first worker crash
	lock_guard< mutex > lock_crash( crash_lock );
	if ( ! worker_crashed )
	{
		worker_crashed = true;
		user_exception = user_excpt;

		if ( signum >= 0 )
		{
			plog( err_msg1 );
			signal_handler( signum );
		}
		else
		{
			if ( error_hard_thread )
				error_hard( error_hard_msg1, error_hard_msg3, true, error_hard_msg2 );
			else
			{
				if ( pexcpt != nullptr )
				{
					error_hard( err_msg1, err_msg3, true, err_msg2 );
					rethrow_exception( pexcpt );
				}
				else
				{
					if ( var != NULL && var->label != NULL )
						error_hard( "parallel computation problem",
									"disable parallel computation for this variable\nor check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
									true,
									"while computing variable '%s' (object '%s') a multi-threading worker crashed", var->label, var->up->label != NULL ? var->up->label : "(none)" );
					else
						error_hard( "parallel computation problem",
									"disable parallel computation for this variable\nor check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
									true,
									"multi-threading worker crashed" );
				}
			}
		}
	}

	return false;
}


/***************************************************
PARALLEL_UPDATE
Multi-thread scheduler for parallel updating
****************************************************/
void parallel_update( variable *v, object* p, object *caller )
{
	bool ready[ max_threads ], wait = false;
	int i, nt, wait_time;
	clock_t pstart = 0;
	bridge *cb;
	object *co;
	variable *cv = NULL;

	// prevent concurrent parallel update and multi-threading in a single core
	if ( parallel_ready && max_threads > 1 )
		parallel_ready = false;
	else
	{
		v->cal( caller, 0 );
		return;
	}

	// find the beginning of the linked list chain for current object
	cb = p->up->search_bridge( p->label );

	// if single instanced object, update as usual
	if ( cb->head == NULL || cb->head->next == NULL )
	{
		v->cal( caller, 0 );
		return;
	}

	// set ready worker threads
	for ( nt = 0, i = 0; i < max_threads; ++i )
	{
		ready[ i ] = workers[ i ].free;
		if ( ! ready[ i ] )
			++nt;
	}

	if ( nt > 0 )
	{
		error_hard( "parallel computation problem",
					"disable parallel computation for this variable or check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
					true,
					"variable '%s' (object '%s') %d parallel worker(s) crashed", v->label, v->up->label, i );
		return;
	}

	// scan all instances of current object under current parent
	for ( co = cb->head; co != NULL; co = co->next )
	{
		cv = co->search_var( co, v->label );

		// compute only if not updated
		if ( cv != NULL && cv->last_update < t && t >= cv->next_update )
		{
			// if no worker available, wait to free existing ones
			while ( nt >= max_threads )
			{
				// if starting wait, reset chronometer
				if ( ! wait )
				{
					wait = true;
					pstart = clock( );
				}
				else		// already waiting
				{
					wait_time = ( clock( ) - pstart ) / CLOCKS_PER_SEC;
					if ( wait_time > MAX_WAIT_TIME )
					{
						error_hard( "deadlock during parallel computation",
									"disable parallel computation for this variable or check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
									true,
									"variable '%s' (object '%s') took more than %d seconds\nwhile computing value for case %d", cv->label, cv->up->label, MAX_WAIT_TIME, t );
						return;
					}
				}

				// look for free and stopped workers
				for ( i = 0; i < max_threads; ++i )
				{
					workers[ i ].check( );

					if ( ! ready[ i ] && workers[ i ].free )
					{
						--nt;
						ready[ i ] = true;
						wait = false;
					}
				}

				// sleep process until first worker is free
				if ( nt >= max_threads )
				{
					unique_lock< mutex > lock_update( update_lock );
					worker_ready = false;
					if ( ! upd_workers.wait_for ( lock_update, chrono::milliseconds( MAX_TIMEOUT ), [ ]{ return ! worker_ready; } ) )
						{
							worker_ready = true;
							plog( "\nWarning: workers timeout (%d millisecs.), continuing...", MAX_TIMEOUT );
							break;
						}
				}

				// recheck running workers
				for ( i = 0; i < max_threads; ++i )
					workers[ i ].check( );
			}

			// find first free worker
			for ( i = 0; ! ready[ i ] && i < max_threads; ++i );
			// if something go wrong, wait fist worker (always there)
			if ( i >= max_threads )
			{
				error_hard( "parallel computation problem",
							"disable parallel computation for this variable or check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
							true,
							"variable '%s' (object '%s') had a multi-threading inconsistency,\nmaybe a deadlock state", cv->label, cv->up->label );
				return;
			}
			else
			{	// start the computation of the current variable instance in the worker
				++nt;
				ready[ i ] = false;
				workers[ i ].cal( cv );
			}
		}
	}

	// wait last threads finish processing
	while ( nt > 0 )
	{	// if starting wait, reset chronometer
		if ( ! wait )
		{
			wait = true;
			pstart = clock( );
		}
		else		// already waiting
		{
			wait_time = ( clock( ) - pstart ) / CLOCKS_PER_SEC;
			if ( wait_time > MAX_WAIT_TIME )
			{
				error_hard( "deadlock during parallel computation",
							"disable parallel computation for this variable or check your equation code to prevent this situation.\n\nPlease choose 'Quit LSD Browser' in the next dialog box",
							true,
							"variable '%s' (object '%s') took more than %d seconds\nwhile computing value for case %d", cv != NULL ? cv->up->label : "", cv != NULL ? cv->label : "", MAX_WAIT_TIME, t );
				return;
			}
		}

		// wait till each thread finishes
		for ( i = 0; i < max_threads; ++i )
		{
			if ( ! ready[ i ] && workers[ i ].free )
			{
				--nt;
				ready[ i ] = true;
				wait = false;
			}

			// check worker problem
			workers[ i ].check( );
		}
	}

	// re-enable concurrent parallel update
	parallel_ready = true;
}

#endif

/****************************************************
WORKER_ERRORS
Check how many workers are in error condition
****************************************************/
int worker_errors( void )
{
#ifndef _NP_

	int i, count;

	if ( workers == NULL )
		return 0;

	for ( count = i = 0; i < max_threads; ++i )
		if ( workers[ i ].errored )
			++count;

	return count;

#else

	return 0;

#endif
}
