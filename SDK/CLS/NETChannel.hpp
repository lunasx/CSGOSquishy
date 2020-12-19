
/*MIT License

Copyright(c) 2020 Black

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


https://github.com/xBlack40/CSGOSquishy/blob/main/LICENSE */

#pragma once

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		

class i_net_channel_info
{
public:

	enum
	{
		GENERIC = 0,	
		LOCALPLAYER,	
		OTHERPLAYERS,	
		ENTITIES,		
		SOUNDS,			
		EVENTS,			
		USERMESSAGES,	
		ENTMESSAGES,	
		VOICE,			
		STRINGTABLE,	
		MOVE,			
		STRINGCMD,		
		SIGNON,			
		TOTAL,			
	};

	virtual const char  *get_name(void) const = 0;	
	virtual const char  *get_address(void) const = 0; 
	virtual float		get_time(void) const = 0;	
	virtual float		get_time_connected(void) const = 0;	
	virtual int			get_buffer_size(void) const = 0;	
	virtual int			get_data_rate(void) const = 0; 

	virtual bool		is_loop_back(void) const = 0;	
	virtual bool		is_timing_out(void) const = 0;	
	virtual bool		is_play_back(void) const = 0;	

	virtual float		get_latency(int flow) const = 0;	 
	virtual float		get_average_latency(int flow) const = 0; 
	virtual float		get_average_loss(int flow) const = 0;	
	virtual float		get_average_choke(int flow) const = 0;	 
	virtual float		get_average_data(int flow) const = 0;	
	virtual float		get_average_packets(int flow) const = 0; 
	virtual int			get_total_data(int flow) const = 0;	
	virtual int			get_sequence_number(int flow) const = 0;	
	virtual bool		is_valid_packet(int flow, int frame_number) const = 0;
	virtual float		get_packet_time(int flow, int frame_number) const = 0; 
	virtual int			get_packet_bytes(int flow, int frame_number, int group) const = 0; 
	virtual bool		get_stream_progress(int flow, int *received, int *total) const = 0; 
	virtual float		get_since_last_time_recieved(void) const = 0;	
	virtual	float		get_command_interpolation_ammount(int flow, int frame_number) const = 0;
	virtual void		get_packet_response_latency(int flow, int frame_number, int *pnLatencyMsecs, int *pnChoke) const = 0;
	virtual void		get_remote_framerate(float *pflFrameTime, float *pflFrameTimeStdDeviation) const = 0;

	virtual float		get_timeout_seconds() const = 0;
};