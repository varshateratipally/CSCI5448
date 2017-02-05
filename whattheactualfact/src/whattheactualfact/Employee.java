package whattheactualfact;
import java.time.LocalDate;
import java.time.Month;
import java.time.Period;

public class Employee
{
	public String firstName="";
	public String lastName="";
	public LocalDate dateOfBirth=LocalDate.of(1990,Month.JANUARY,1);
	public String uniqueId="123456789";// all UIDS 9 Characters DepartmentPosition-XXX-XXXX
	public int contactNumber=0;
	public LocalDate joiningDate=LocalDate.of(2000,Month.JANUARY,1);
	public int age=0;
	public int yearsInCompany=0;
	public CompanyPositions position=null;
	public CompanyDepartments department=null;
	
	protected enum CompanyPositions
	{
		INTERN,ENTRY_LEVEL,MANAGER
	}
	
	protected enum CompanyDepartments
	{
		HR,RND,MANUFACTURING,SALES
	}
	
	public Employee()
	{
		
	}
	
	public Employee(String _firstname, String _lastname, LocalDate _dateofbirth, String _uniqueid, int _contactnumber,LocalDate _joiningdate)
	{
		this.firstName=_firstname;
		this.lastName=_lastname;
		this.dateOfBirth=_dateofbirth;
		this.uniqueId=_uniqueid;
		this.contactNumber=_contactnumber;
		this.joiningDate =_joiningdate;
		if ((this.dateOfBirth != null) && (whattheactualfact.currentDate != null)) 
		{
			this.age= Period.between(this.dateOfBirth, whattheactualfact.currentDate).getYears();
        } 
		if ((this.joiningDate != null) && (whattheactualfact.currentDate != null)) 
		{
			this.yearsInCompany= Period.between(this.joiningDate, whattheactualfact.currentDate).getYears();
        }
		if(this.uniqueId != "")
		{
			switch(this.uniqueId.charAt(0))
			{
				case '1':
					this.department=CompanyDepartments.HR;
				case '2':
					this.department=CompanyDepartments.MANUFACTURING;
				case '3':
					this.department=CompanyDepartments.SALES;
				case '4':
					this.department=CompanyDepartments.RND;
				default:
					;
			}
			switch(this.uniqueId.charAt(1))
			{
				case '1':
					this.position=CompanyPositions.INTERN;
				case '2':
					this.position=CompanyPositions.ENTRY_LEVEL;
				case '3':
					this.position=CompanyPositions.MANAGER;
				default:
					;
			}
		}
		System.out.println(this.firstName);
		
		
	} 

	public String getFirstName()
	{
		return firstName;
	}

	public void setFirstName(String firstname)
	{
		this.firstName = firstname;
	}

	public String getLastName()
	{
		return lastName;
	}

	public void setLastName(String lastname)
	{
		this.lastName = lastname;
	}

	public String getUniqueId()
	{
		return uniqueId;
	}
	
	public void setUniqueId(String uniqueid)
	{
		this.uniqueId = uniqueid;
	}

	public LocalDate getDateOfBirth()
	{
		return dateOfBirth;
	}

	public void setDateOfBirth(LocalDate dateOfBirth)
	{
		this.dateOfBirth = dateOfBirth;
	}

	

	public int getContactNumber()
	{
		return contactNumber;
	}

	public void setContactNumber(int contactnumber)
	{
		this.contactNumber = contactnumber;
	}

	public LocalDate getJoiningDate()
	{
		return joiningDate;
	}

	public void setJoiningDate(LocalDate joiningdate)
	{
		this.joiningDate = joiningdate;
	}
	
	
	//Defined by instance variables so no setter
	public int getAge()
	{
		return this.age;
	}

	public int getYearsInCompany()
	{
		return yearsInCompany;
	}

	public CompanyPositions getPosition()
	{
		return position;
	}

	public CompanyDepartments getDepartment()
	{
		return department;
	}
	
	
}

