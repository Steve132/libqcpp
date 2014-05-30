#ifndef QREGISTER_H
#define QREGISTER_H

#include<initializer_list>
#include<cstdint>
#include<iostream>
#include<memory>

#define REG_MAX_SIZE_BITS 7			//log(sizeof(cl_long)*8) (+1) (64 can be stored there)
#define REG_MAX_MASK ((1<<REG_MAX_SIZE_BITS)-1)
#define REG_MAX_SIZE      (1<<(REG_MAX_SIZE_BITS-1))

//MAX_REG_SIZE_BITS 6
//MAX_REGISTER_SIZE (1 << MAX_REG_SIZE_BITS)
//register_profile_t is a size_t long (or 64)...
//Each distinct argument size in order is given as an array in the lower MAX_REG_SIZE_BITS;

class QRegister;
class QMachine;
class QOperationRecord;

struct permutation_t
{
	////this is output[i]=input[index[i]]
	char indices[REG_MAX_SIZE];
	permutation_t inverse() const;
	permutation_t();
	permutation_t(const std::initializer_list<char>&);
};

class QRegister
{
public:
	const permutation_t definition;
	QMachine& parent_machine;
	const std::size_t num_bits;
	
	QRegister(QMachine& m,const permutation_t& d,const std::size_t& nb):parent_machine(m),definition(d),num_bits(nb)	//ALWAYS initialized to |0> |0>
	{}
	QRegister(QMachine& m,const std::initializer_list<char>& ilst):parent_machine(m),definition(ilst),num_bits(ilst.size())	//ALWAYS initialized to |0> |0>
	{}
	
	QOperationRecord operator+=(const int);	
	QOperationRecord operator-=(const int);
	QOperationRecord operator<<=(const std::size_t); 	//CIRCULAR shifts because operations must be reversible
	QOperationRecord operator>>=(const std::size_t); 
	QOperationRecord operator^=(const std::size_t);
	
	QOperationRecord operator+=(const QRegister&);	//Not necessary
	QOperationRecord operator-=(const QRegister&);
	QOperationRecord operator<<=(const QRegister&); 	//CIRCULAR shifts because operations must be reversible
	QOperationRecord operator>>=(const QRegister&); 
 	QOperationRecord operator^=(const QRegister&);
		
	QRegister subreg(std::size_t beginning,std::size_t end);
private:
	//QRegister& operator=	//Registers can't be copied.  They are really references to machine ram..but the reliance on the machine ensures this
};

class QOperationRecord
{
public:
	QRegister resultreg;
	QOperationRecord(const QRegister& rr):resultreg(rr)
	{}
	operator QRegister&()
	{
		return resultreg;
	}
};

QOperationRecord invert(QRegister& r);
QOperationRecord measure(QRegister& r);

std::ostream& operator<<(std::ostream& out,QRegister& mac);

#endif