# Accounting App

![image](ressources/gestion-comptable.jpg)

The goal of this project is to create a cash management software for an association, using
the principles of double-entry accounting. The user must be able to define different accounts according to
according to his needs, enter and correct transactions, and generate different documents related to his
accounting (balance sheet and income statement).

## Elements of realization
### Graphical interface
The software can first be developed in command line with menus and simple displays of the different
of the different accounts. For the LO21 students, a Qt graphical interface will be developed
to facilitate the consultation, the input and modification of information, and the visualization of reports.

### Summary of the operations to be performed
The operations expected by the application are :
- add/remove/highlight accounts
- add/correct/delete simple and distributed transactions
- calculate the balance of an account
- create a closure
- reconcile an account
- edit accounting documents
- manage the persistence of information (files, database, etc.)
- save the context: when the application is started, the state of the application and the settings
present at the time of the last execution are retrieved.

## Expected deliverables

The deliverable is composed of the following elements:
- Source code: all the source code of the project. Caution, do not provide an executable or
object file.
- Documentation: a complete html documentation generated with Doxygen.
- Presentation video with audio comments: a short presentation video in which you will film and comment on
in which you will film and comment your software in order to demonstrate the correct operation of each expected
each expected functionality (max 10 min).
- Report: A report in .pdf format composed of 3 parts:
    - a summary of what your application allows (specifying among the expected operations those that have been implemented and those that have not);
    - a description of your architecture, justifying the architecture choices;
    - a detailed argumentation where you show that your architecture easily allows for evolutions ;

You can add in the appendix of this report instructions for your grader if necessary (presentation of the deliverables, compilation instructions, etc.).
This report should be concise and not exceed 20 pages if possible (including annexes).
