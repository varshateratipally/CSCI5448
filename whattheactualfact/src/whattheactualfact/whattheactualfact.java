package whattheactualfact;
import java.time.LocalDate;

public class whattheactualfact
{
	public static LocalDate currentDate= LocalDate.now();
	
	
	public static void main(String[] args)
	{
		Employee George = new EmployeeBuilder().buildFirstName("George").buildEmployee();
	}

}
