/* CSCI261B Assignment7: Tarbomb Class
 *
 * Description: Declaration file for Tarbomb Class
 *
 * Author: Joseph McKinsey
 *
 */

#ifndef TARBOMB
#define TARBOMB

using namespace std;

// Declare tarbomb class.
class Tarbomb {
    public:
        Tarbomb();
        void setShellString(string shell);
        void setFailMessage(string fail);
        void setSuccessMessage(string success);
        void setTimeLimit(double timeInput);
        void introduction();
        void activate();
    private:
        string shell;
        string failMessage;
        string successMessage;
        double timeLimit;
        bool checkInput(string input);
        void endGameMessage(string input);
};

#endif
