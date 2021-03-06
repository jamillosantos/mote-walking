/**
 * @author J. Santos <jamillo@gmail.com>
 * @date September 28, 2016
 */

#ifndef WALKING_MOTORS_MOTOR_H
#define WALKING_MOTORS_MOTOR_H

#include <boost/optional.hpp>

namespace mote
{
namespace walking
{
namespace motors
{
template <typename T>
class Value
{
private:
	boost::optional<T> lastWriteValue;
	boost::optional<T> writeValue;
	boost::optional<T> readValue;
public:
	/**
	 * Set the value for writting.
	 *
	 * @param value
	 * @return
	 */
	Value& operator=(T value)
	{
		if ((!this->lastWriteValue) || (this->lastWriteValue != value))
			this->writeValue = value;
		return *this;
	}

	/**
	 * If there is a value to be written.
	 * @return
	 */
	bool is_dirty()
	{
		return this->writeValue.is_initialized();
	}

	/**
	 * Value read.
	 *
	 * @return
	 */
	const boost::optional<T> &read() const
	{
		return this->readValue;
	}

	/**
	 * Value to be written.
	 *
	 * @return
	 */
	const boost::optional<T> &toWrite() const
	{
		return this->writeValue;
	}

	/**
	 * Set the read value.
	 *
	 * @param value
	 */
	void read(T value)
	{
		this->readValue = value;
	}

	void write()
	{
		if (this->writeValue)
			this->lastWriteValue = this->writeValue;
		else
			this->lastWriteValue.reset();
	}

	/**
	 * Clear the write value.
	 */
	void clear()
	{
		this->writeValue.reset();
	}
};

class Servo
{
public:
	Value<double> speed;
	Value<double> angle;

	bool inverted;

	Servo(bool inverted);

	Servo();
};
}
}
}


#endif //WALKING_MOTORS_MOTOR_H
