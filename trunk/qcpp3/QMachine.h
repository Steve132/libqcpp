#ifndef QMACHINE_H
#define QMACHINE_H

#define __CL_ENABLE_EXCEPTIONS 
#include<CL/cl.hpp>
#include<vector>
#include<string>
#include<cstdlib>
#include<complex>
#include<memory>

class QGate;
class QMachine
{
protected:
	cl::Context context;
	std::vector<cl::Device> devices;
	mutable cl::CommandQueue queue;
	
	std::size_t debug;
	
	cl::Buffer buf[2];
	friend class QGate;
	
	cl::Buffer* prev;
	cl::Buffer* next;
	
	cl::Event prevevent;
	std::complex<float>* lockptr;
	
	std::shared_ptr<QGate> permutation_gate;
public:
	const std::size_t num_bits;
	const std::size_t num_states;
	
	QMachine(std::size_t nb,bool deb=false);
	
	const std::complex<float>* lock();
	void unlock();
protected:
	void run_gate_kernel(cl::Kernel& kern,cl_ulong regspec);
};

std::ostream& operator<<(std::ostream& out,QMachine& mac);

#endif