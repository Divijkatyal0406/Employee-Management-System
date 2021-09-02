#include<bits/stdc++.h>
using namespace std;

#define minTarget 5

class ManagingDirector{
    public:
        virtual void printMD()=0;
};

class CEO: public ManagingDirector{
    public:
        void printMD(){
            cout<<"MD of the company is Rahul Sachdeva"<<endl;
        }
};

class Employee{
    private:
        int attendance;
    public:
        string name;
        string department;
        string ID;
        int noOfProjects;
        int leave;
        string company;
        int experience;
        int salary;
        int monthlyTarget;

        friend class HR;
};

void printAllEmployees(vector<string> &names){
            if(names.empty()){
                cout<<"No employee data found"<<endl;
            }
            for (auto idx = names.begin(); idx != names.end(); idx++)
                cout <<*idx<<endl;
}
        
// string bestPerformer(Manager* ManagerArr,int n){
//             int ans=-1;
//             string ansName;
//             for (int i = 0; i < n; i++)
//             {
//                 ans=max(ans,ManagerArr[i].noOfProjects);
//             }
//             for (int i = 0; i < n; i++)
//             {
//                 if(ans==ManagerArr[i].noOfProjects){
//                     ansName=ManagerArr[i].name;
//                 }
//             }
//             return ansName;
            
//         }

istream &operator>>(istream  &input, Employee &E) { 
        cout<<"Enter name of the Employee"<<endl;
        input>>E.name;
        cout<<"Enter the salary of the Employee"<<endl;
        input>>E.salary;
        cout<<"Enter the experience of the Employee"<<endl;
        input>>E.experience;
        return input;            
}
    
class Manager: public Employee{
	public:
		double budget;
		double deduction;
		Manager(){
            cout<<"Enter employee name "<<endl;
            cin>>name;
            this->name=name;
            cout<<"Enter employee salary "<<endl;
            cin>>salary;
            this->salary=salary;
            cout<<"Enter employee experience "<<endl;
            cin>>experience;
            this->experience=experience;
            cout<<"Enter budget "<<endl;
            cin>>budget;
            this->budget=budget;
            cout<<"Enter the deduction "<<endl;
            cin>>deduction;
            this->deduction=deduction;
		}
        ~Manager(){}
		virtual int appraisalScore(int experience,int attendance,int noOfProjects){
            int score;
			score=experience + attendance + noOfProjects*2;
			return score;
		}
		void maintainBudget(){
			map<string, double>BudgetMap;
            double x=0.20*budget;
            double y=0.28*budget;
            double z=0.25*budget;
            double k=0.27*budget;
			BudgetMap.insert(pair<string,double>("Sales Department", x));
			BudgetMap.insert(pair<string,double>("Marketing Department", y));
			BudgetMap.insert(pair<string,double>("Technical Department", z));
			BudgetMap.insert(pair<string,double>("HR Department", k));
			map<string, double>:: iterator itr;
			
			for (itr=BudgetMap.begin(); itr!=BudgetMap.end(); itr++){
				cout<<(*itr).first<<" "<<(*itr).second<<endl;
			}

			
		}
	void monitorEmployee(Employee &e){
        cout<<"Enter the leaves of an employee"<<endl;
        cin>>e.leave;
        if(e.noOfProjects<5){
			cout<<"Give a warning to the employee"<<endl;
		}
		try{
			if (e.leave==1){
				throw deduction;
			}
            else{
                double deduction= e.leave*(salary/30);
                cout<<"Deduction is "<<deduction<<endl;
            }
		}
			catch(...){
				cout<<"No deduction in salary"<<endl;
			}
		}
	
};


class HR:public Employee{
    public:
        string department="HR DEPARTMENT";
        HR(){
            cout<<"Enter employee name who is accessing the system"<<endl;
            cin>>name;
            this->name=name;
            cout<<"Enter employee salary who is accessing of the system"<<endl;
            cin>>salary;
            this->salary=salary;
            cout<<"Enter employee experience who is accessing of the system"<<endl;
            cin>>experience;
            this->experience=experience;
        }
        string hrID="HR1001";
        ~HR(){}
        void showEmplyData(){
            hrID="HR1001"+this->name;
            cout<<"Employee name is "<<this->name<<endl;
            cout<<"Employee salary is "<<this->salary<<endl;
            cout<<"Employee experience is "<<this->experience<<endl;
            cout<<"HR DEPARTMENT"<<endl;
            cout<<"Employee id is "<<hrID<<endl;
        }
        void updateEmployeeID(vector<string> &ids,string prevID,string newID){
            bool check=true;
            auto idx = find(ids.begin(),ids.end(), prevID);
            int indexOfEmployee;
            if (idx != ids.end())
            {
                indexOfEmployee = idx - ids.begin();
            }
            else {
                cout <<"Employee ID doesn't exist"<< endl;
                check=false;
            }
            if(check){
                cout <<"Employee ID updated successfully"<< endl;
            }
            ids[indexOfEmployee]=newID;
        }
        void employeeAppraisal(int experience,int attendance,int noOfProjects){
            Manager *m1;
            int score=m1->appraisalScore(experience,attendance,noOfProjects);
            if(score<50){
                cout <<"Employee is eligible for 2.5% increment"<< endl;
            }
            else{
                cout <<"Employee is eligible for 5% increment"<< endl;
            }
        }
        void deleteEmployee(vector<string> &names,vector<string> &ids,string name,string ID){
            auto idxN = find(names.begin(),names.end(), name);
            names.erase(idxN);
            auto idxI = find(ids.begin(),ids.end(), ID);
            ids.erase(idxI);
            if(idxN==names.end()){
                cout<<"Employee deleted successfully"<<endl;
            }
            else{
                cout<<"Employee not found"<<endl;
            }
        }
        void newEmployee(vector<string> &names,vector<string> &ids,string name,string ID){
            names.push_back(name);
            ids.push_back(ID);
        }
        void newHiring(queue<pair<string,int>> &q){
            pair<string,int> p;
            while(!q.empty()){
                p=q.front();
                q.pop();
                if(p.second>10){
                    cout<<p.first<<" "<<"is eligible for this job"<<endl;
                }
                else{
                    cout<<p.first<<" "<<"is not eligible for this job"<<endl;
                }
            }


        }
};

class GM: public Manager{
    public:
        int monthlyTarget;
        void target(Employee &e){
            if (e.monthlyTarget>minTarget){
                cout<<"Target Completed"<<endl;
            }
            else{
                cout<<"Target not completed"<<endl;
            }
        }
        inline void monitorEmployee(int leave){
			if (leave>10)
			{
				cout<<"Employee is suspended"<<endl;
			}
        }
};

class ProjectManager: public Employee{
    public:
        //number of members in a project
        int nomip;
        //queue<string> problems; 
        vector<double> budget;
        vector<int> severity;
        double totalBudget;
        ProjectManager(double totalBudget,int nomip)
        {
            this->totalBudget=totalBudget;
            this->nomip=nomip;
        }
        //ProjectManager(){}
        ~ProjectManager(){}
        void newProblem(string problem,queue<string> problems)
        {
            problems.push(problem);
            cout<<"Your problem is feed successfully"<<endl;
        }
        void solvedproblem(int severity,queue<string> problems)
        {   
            string problem;
            while(!problems.empty()){
                problem=problems.front();
                problems.pop();
            }
        }
        void solvedproblem(queue<string> problems)
        {   
            int noOfProblems=0;
            if(problems.empty()){
                cout<<"No problems so far"<<endl;
            }
            while(!problems.empty()){
                problems.pop();
                noOfProblems++;
            }
            cout<<noOfProblems<<" problems are resolved"<<endl;
        }
            
        void budgetAllotment(int nomip)
        {
            double budget=nomip*100000/20;
            cout<<budget<<" "<<"is required"<<endl;
        }

        void progressManager(queue<string> problems)
        {
            if (problems.empty())
                cout << " Problems is solved"<<endl;
            else
                cout << " There's work to do"<<endl;
        }
};

int main(){
    vector<string> names;
    vector<string> ids;
    queue<string> problems; 
    names.push_back("Raghav");
    ids.push_back("2020HR");

    names.push_back("Rahul");
    ids.push_back("2020GM");
    
    int option;
    char ch;
    do{
        cout<<"**************************MENU***************************"<<endl;
        cout<<"1.  Show HR employees data"<<endl;
        cout<<"2.  Show alloted budget to different departments"<<endl;
        cout<<"3.  Show leave and project status of employee"<<endl;
        cout<<"4.  Update employee's ID"<<endl;
        cout<<"5.  Show appraisal of employee"<<endl;
        cout<<"6.  Delete Employee from the database"<<endl;
        cout<<"7.  Show all Employees"<<endl;
        cout<<"8.  See new hiring updates"<<endl;
        cout<<"9. Show the best employee of the month"<<endl;
        cout<<"10. Enter a new problem"<<endl;
        cout<<"11. Show number of problems resolved so far"<<endl;
        cout<<"12. Show the budget required for the project"<<endl;

        cin>>option;
        switch (option)
            {
                case 1:
                {
                    HR h=HR();
                    h.showEmplyData();
                    break;
                }
                case 2:
                {
                    Manager m=Manager();
                    m.maintainBudget();
                    break;
                }
                case 3:
                {
                    Manager m=Manager();
                    Employee e;
                    m.monitorEmployee(e);
                    break;
                }
                case 4:
                {
                    HR h1=HR();
                    string newID;
                    cout<<"Enter new ID"<<endl;
                    cin>>newID;
                    string oldID;
                    cout<<"Enter old ID"<<endl;
                    cin>>oldID;
                    h1.updateEmployeeID(ids,oldID,newID);
                    break;
                }
                case 5:
                {
                    HR h2=HR();
                    int experience;
                    cout<<"Enter the experience"<<endl;
                    cin>>experience;
                    int attendance;
                    cout<<"Enter the attendance"<<endl;
                    cin>>attendance;
                    int numberOfProjects;
                    cout<<"Enter the number of projects"<<endl;
                    cin>>numberOfProjects;
                    h2.employeeAppraisal(experience,attendance,numberOfProjects);
                    break;
                }
                case 6:
                {
                    HR h3=HR();
                    string name;
                    cout<<"Enter the name of the Employee to be deleted"<<endl;
                    cin>>name;
                    string ID;
                    cout<<"Enter the ID of the Employee to be deleted"<<endl;
                    cin>>ID;
                    h3.deleteEmployee(names,ids,name,ID);
                    break;
                }
                case 7:{
                    printAllEmployees(names);
                    break;
                }
                case 8:{
                    HR h5=HR();
                    queue<pair<string,int>> q;
                    string name;
                    cout<<"Enter the name of the aspiring candidate"<<endl;
                    cin>>name;
                    int experience;
                    cout<<"Enter the experience of aspiring candidate"<<endl;
                    cin>>experience;
                    q.push({name,experience});
                    h5.newHiring(q);
                    break;
                }
                case 9:{
                    string problem;
                    cout<<"Raise the ticket for new problem"<<endl;
                    cin>>problem;
                    ProjectManager p(1002,12);
                    p.newProblem(problem,problems);
                    break;
                }
                case 10:
                {
                    ProjectManager p1(1002,12);
                    p1.solvedproblem(problems);
                    break;
                }
                case 11:
                {
                    int nomip;
                    cout<<"Enter the number of members in the project"<<endl;
                    cin>>nomip;
                    ProjectManager p2(1002,12);
                    p2.budgetAllotment(nomip);
                    break;
                }
                case 12:
                {
                    ProjectManager p3(1002,12);
                    p3.progressManager(problems);
                }
                default:
                {
                    cout<<"Invalid option"<<endl;
                    break; 
                }   
            }
            cout<<"If you want to continue press 'y' else press 'n' "<<endl;
            cin>>ch;
    }while(ch=='y');

    return 0;
}