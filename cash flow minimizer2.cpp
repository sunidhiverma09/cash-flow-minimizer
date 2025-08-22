#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTIES 100

// Function to calculate the net amount each party owes or is owed
void calculateNetAmounts(int transactions[][3], int numTransactions, int netAmounts[], int numParties) {
	int i;
    for (i = 0; i < numTransactions; i++) {
        int debtor = transactions[i][0];
        int creditor = transactions[i][1];
        int amount = transactions[i][2];
        
        netAmounts[debtor] -= amount;
        netAmounts[creditor] += amount;
    }
}

// Function to find the minimum cash flow to settle all debts
int minimizeCashFlow(int netAmounts[], int numParties) {
    int transactions = 0;

    while (1) {
        // Find the maximum creditor (maximum positive net amount)
        int maxCreditor = 0;
        int maxCreditorIndex = -1;
        int i;
        for (i = 0; i < numParties; i++) {
            if (netAmounts[i] > maxCreditor) {
                maxCreditor = netAmounts[i];
                maxCreditorIndex = i;
            }
        }

        // Find the maximum debtor (maximum negative net amount)
        int maxDebtor = 0;
        int maxDebtorIndex = -1;
        for (int i = 0; i < numParties; i++) {
            if (netAmounts[i] < maxDebtor) {
                maxDebtor = netAmounts[i];
                maxDebtorIndex = i;
            }
        }

        // If no debts are left, break
        if (maxCreditor == 0 && maxDebtor == 0) {
            break;
        }

        // Settle the debt between maxDebtor and maxCreditor
        int settlementAmount = (maxCreditor < -maxDebtor) ? maxCreditor : -maxDebtor;
        netAmounts[maxCreditorIndex] -= settlementAmount;
        netAmounts[maxDebtorIndex] += settlementAmount;

        printf("Person %d pays Person %d an amount of %d\n", maxDebtorIndex, maxCreditorIndex, settlementAmount);
        transactions++;
    }

    return transactions;
}

int main() {
    int numParties, numTransactions;
    printf("Enter the number of parties: ");
    scanf("%d", &numParties);
    printf("Enter the number of transactions: ");
    scanf("%d", &numTransactions);

    int transactions[numTransactions][3];
    printf("Enter the transactions (debtor, creditor, amount):\n");
    int i;
    for ( i = 0; i < numTransactions; i++) {
        scanf("%d %d %d", &transactions[i][0], &transactions[i][1], &transactions[i][2]);
    }

    int netAmounts[MAX_PARTIES] = {0};
    calculateNetAmounts(transactions, numTransactions, netAmounts, numParties);

    int result = minimizeCashFlow(netAmounts, numParties);
    printf("Total number of transactions required: %d\n", result);

    return 0;
}

