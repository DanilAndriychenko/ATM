#pragma once

class Tester
{
public:
    
    static void runTests();

private:
    static void authenticateExistingUser();
    static void authenticateAdmin();
    static void authenticateUnknownCardNumber();

    static void testAdminCashingIn();
    static void testAdminCashOut();
    
    static void testClientCashIn();
    static void testClientCashOut();
    static void testExpiredCard();

    static void selfTransaction();
    static void testNotEnoughMoneyCase();
    static void testOurBankTransactionCommission();
    static void testAnotherBankTransactionCommission();
};
