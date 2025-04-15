#include <ENgines/Inc/Engines.h>

using namespace ENgines;
using namespace ENgines::Core;

static int sUniqueId = 0;
class Student 
{
public:
	Student()
	{
		mId = ++sUniqueId;
	}

	void SetName(const std::string& name)
	{
		mName = name;
	}
private:
	int mId = 0;
	std::string mName;
};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);

	std::vector<Student*> students;
	for (uint32_t i = 0; i < 100; ++i)
	{
		Student* newStudent = studentPool.New();
		students.push_back(newStudent);
	}

	for (uint32_t i = 0; i < 60; ++i)
	{
		Student* student = students.back();
		studentPool.Delete(student);
		students.pop_back();
	}

	for (uint32_t i = 0; i < 155; ++i)
	{
		Student* student = studentPool.New();
		students.push_back(student);
	}

	for (Student* student : students)
	{

	}

	return(0);
}