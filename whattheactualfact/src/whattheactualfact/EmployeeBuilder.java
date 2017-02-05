package whattheactualfact;

import java.time.LocalDate;

public class EmployeeBuilder extends Employee
{
	
	public EmployeeBuilder()
	{
		
	}
	
	public Employee buildEmployee()
	{
		return new Employee(this.firstName,this.lastName,this.dateOfBirth,this.uniqueId,this.contactNumber,this.joiningDate);
	}

	public EmployeeBuilder buildFirstName(String _firstName)
	{
		this.firstName = _firstName;
		return this;
	}

	public EmployeeBuilder buildLastName(String _lastName)
	{
		this.lastName = _lastName;
		return this;
	}

	public EmployeeBuilder buildDateOfBirth(LocalDate _dateOfBirth)
	{
		this.dateOfBirth = _dateOfBirth;
		return this;
	}

	public EmployeeBuilder buildUniqueId(String _uniqueId)
	{
		this.uniqueId = _uniqueId;
		return this;
	}

	public EmployeeBuilder buildContactNumber(int _contactNumber)
	{
		this.contactNumber = _contactNumber;
		return this;
	}

	public EmployeeBuilder buildJoiningDate(LocalDate _joiningDate)
	{
		this.joiningDate = _joiningDate;
		return this;
	}
	
	

}
