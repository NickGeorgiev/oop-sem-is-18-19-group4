#include<iostream>

// Student = {
//   facultyNumber -> int/size_t,
//   avg_grades -> double/float,
//   name -> char[30]
// }


void greetStudent(const char name[], int fn, double grades){
    std::cout << "Hello ";
    std::cout << name << "!\n";
    std::cout << "FN: " << fn << '\n';
    std::cout << "Avg. grades: " << grades << '\n';
}

int main() {
  //work with multiple students - arrays introduced
  int fNs[3] = { 71001, 71002, 71003};
  double avg_grades_all[3] = { 5.25, 4.5, 6};
  char names[3][30] = {
    "Student1",
    "Student2",
    "Student3"
  };

  for(int i=0;i<3;i++) {
    std::cout << "fn: " << fNs[i] << '\n';
    std::cout << "name: " << names[i] << '\n';
    std::cout << "grades: " << avg_grades_all[i] << '\n'; 
  }

  //parse it to a function
  greetStudent("Student4", 71004,3.25);

  return 0;
}