#ifndef _encoder_h_
#define _encoder_h_

#include "pidmap.h"
#include <string>
#include <pthread.h>

class Encoder
{
	private:

		enum
		{
			IOCTL_VUPLUS_SET_VPID			= 1,
			IOCTL_VUPLUS_SET_APID			= 2,
			IOCTL_VUPLUS_SET_PMTPID			= 3,
			IOCTL_VUPLUS_START_TRANSCODING	= 100,
			IOCTL_VUPLUS_STOP_TRANSCODING	= 200,
		};

		Encoder();
		Encoder(const Encoder &);

		pthread_t	start_thread;
		bool		start_thread_running;
		bool		start_thread_joined;
		bool		stopped;
		int			fd;
		int			id;
		PidMap		pids;

		static void* start_thread_function(void *);

	public:

		Encoder(const PidMap &, std::string default_frame_size) throw(std::string);
		~Encoder()												throw();

		std::string	getprop(std::string)				const	throw(std::string);
		void		setprop(std::string, std::string)	const	throw(std::string);

		bool		start_init()								throw();
		bool		start_finish()								throw();
		bool		stop()										throw();

		int			getfd()								const	throw();
		PidMap		getpids()							const	throw();
};

#endif
