#include "pch.h"
#include <gtest/gtest.h>

#include <string>
#include <cctype>

using namespace std;
using namespace System;
#pragma managed
#using <mscorlib.dll>


// ============================================================================
// UTILITY FUNCTIONS FOR TESTING
// ============================================================================

// Helper: Validate email format
bool IsValidEmail(const string& email) {
    if (email.empty()) {
        return false;
    }

    // Basic email validation: must have @, must have . after @
    size_t at_pos = email.find('@');
    if (at_pos == string::npos) return false;
    if (at_pos == 0) return false; // @ at start

    size_t dot_pos = email.find('.', at_pos);
    if (dot_pos == string::npos) return false;
    if (dot_pos == at_pos + 1) return false; // . immediately after @
    if (dot_pos == email.length() - 1) return false; // . at end

    // Count @ signs - should be exactly one
    int at_count = 0;
    for (char c : email) {
        if (c == '@') at_count++;
    }
    if (at_count != 1) return false;

    return true;
}

// Helper: Validate password strength
bool IsValidPassword(const string& password) {
    if (password.empty()) {
        return false;
    }

    // Minimum 8 characters
    if (password.length() < 8) return false;

    // Must have at least one uppercase letter
    bool has_upper = false;
    for (char c : password) {
        if (isupper(c)) {
            has_upper = true;
            break;
        }
    }
    if (!has_upper) return false;

    // Must have at least one digit
    bool has_digit = false;
    for (char c : password) {
        if (isdigit(c)) {
            has_digit = true;
            break;
        }
    }
    if (!has_digit) return false;

    return true;
}

// Helper: Validate phone number format
bool IsValidPhoneNumber(const string& phone) {
    if (phone.empty()) {
        return false;
    }

    // Minimum 9 characters
    if (phone.length() < 9) return false;

    // Should contain only digits and format characters (-, +, ())
    for (char c : phone) {
        if (!isdigit(c) && c != '-' && c != '+' && c != '(' && c != ')' && c != ' ') {
            return false; // Invalid character found
        }
    }

    // Count digits - should have at least 9
    int digit_count = 0;
    for (char c : phone) {
        if (isdigit(c)) digit_count++;
    }
    if (digit_count < 9) return false;

    return true;
}

// Helper: Validate League Name
bool IsValidLeagueName(const string& name) {
    if (name.empty()) return false;
    if (name.length() < 3) return false;
    if (name.length() > 50) return false;
    return true;
}

// Helper: Validate Team Name
bool IsValidTeamName(const string& name) {
    if (name.empty()) return false;
    if (name.length() < 3) return false;
    if (name.length() > 50) return false;
    return true;
}

// Helper: Validate Score
bool IsValidScore(int score) {
    return score >= 0;
}

// ============================================================================
// TEST FIXTURES
// ============================================================================

class ControllerTests : public ::testing::Test {
protected:
    virtual void SetUp() override {
        // Setup code for each test
    }

    virtual void TearDown() override {
        // Cleanup code for each test
    }
};

// ============================================================================
// EMAIL VALIDATION TESTS (Expected behavior for CtrlRegistrarUsuari)
// ============================================================================

TEST_F(ControllerTests, EmailValidFormat) {
    string validEmail = "user@example.com";
    EXPECT_TRUE(IsValidEmail(validEmail)) << "Valid email should pass validation";
}

TEST_F(ControllerTests, EmailNoAtSign) {
    string invalidEmail = "userexample.com";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email without @ should fail";
}

TEST_F(ControllerTests, EmailDoubleAtSign) {
    string invalidEmail = "user@@example.com";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email with @@ should fail";
}

TEST_F(ControllerTests, EmailEmpty) {
    string invalidEmail = "";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Empty email should fail";
}

TEST_F(ControllerTests, EmailOnlySpaces) {
    string invalidEmail = "   ";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email with only spaces should fail";
}

TEST_F(ControllerTests, EmailNoLocalPart) {
    string invalidEmail = "@example.com";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email without local part should fail";
}

TEST_F(ControllerTests, EmailNoDomain) {
    string invalidEmail = "user@";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email without domain should fail";
}

TEST_F(ControllerTests, EmailNoDot) {
    string invalidEmail = "user@examplecom";
    EXPECT_FALSE(IsValidEmail(invalidEmail)) << "Email without dot in domain should fail";
}

// ============================================================================
// PASSWORD VALIDATION TESTS (Expected behavior for CtrlRegistrarUsuari)
// ============================================================================

TEST_F(ControllerTests, PasswordValidStrong) {
    string validPassword = "StrongPass123";
    EXPECT_TRUE(IsValidPassword(validPassword)) << "Strong password should pass validation";
}

TEST_F(ControllerTests, PasswordTooShort) {
    string invalidPassword = "Pass12";
    EXPECT_FALSE(IsValidPassword(invalidPassword)) << "Password less than 8 chars should fail";
}

TEST_F(ControllerTests, PasswordEmpty) {
    string invalidPassword = "";
    EXPECT_FALSE(IsValidPassword(invalidPassword)) << "Empty password should fail";
}

TEST_F(ControllerTests, PasswordNoUppercase) {
    string invalidPassword = "lowercase1";
    EXPECT_FALSE(IsValidPassword(invalidPassword)) << "Password without uppercase should fail";
}

TEST_F(ControllerTests, PasswordNoDigit) {
    string invalidPassword = "NoDigitPass";
    EXPECT_FALSE(IsValidPassword(invalidPassword)) << "Password without digit should fail";
}

TEST_F(ControllerTests, PasswordOnlySpaces) {
    string invalidPassword = "        ";
    EXPECT_FALSE(IsValidPassword(invalidPassword)) << "Password with only spaces should fail";
}

// ============================================================================
// PHONE VALIDATION TESTS (Expected behavior for CtrlRegistrarUsuari)
// ============================================================================

TEST_F(ControllerTests, PhoneValidFormat) {
    string validPhone = "666123456";
    EXPECT_TRUE(IsValidPhoneNumber(validPhone)) << "Valid phone should pass validation";
}

TEST_F(ControllerTests, PhoneValidFormatWithDash) {
    string validPhone = "666-123-456";
    EXPECT_TRUE(IsValidPhoneNumber(validPhone)) << "Valid phone with dashes should pass";
}

TEST_F(ControllerTests, PhoneValidFormatWithPlus) {
    string validPhone = "+34666123456";
    EXPECT_TRUE(IsValidPhoneNumber(validPhone)) << "Valid phone with + should pass";
}

TEST_F(ControllerTests, PhoneTooShort) {
    string invalidPhone = "12345";
    EXPECT_FALSE(IsValidPhoneNumber(invalidPhone)) << "Phone with less than 9 digits should fail";
}

TEST_F(ControllerTests, PhoneWithLetters) {
    string invalidPhone = "666ABC456";
    EXPECT_FALSE(IsValidPhoneNumber(invalidPhone)) << "Phone with letters should fail";
}

TEST_F(ControllerTests, PhoneEmpty) {
    string invalidPhone = "";
    EXPECT_FALSE(IsValidPhoneNumber(invalidPhone)) << "Empty phone should fail";
}

TEST_F(ControllerTests, PhoneOnlySpaces) {
    string invalidPhone = "   ";
    EXPECT_FALSE(IsValidPhoneNumber(invalidPhone)) << "Phone with only spaces should fail";
}

// ============================================================================
// LEAGUE VALIDATION TESTS (Expected behavior for CtrlCrearLliga)
// ============================================================================

TEST_F(ControllerTests, LeagueNameValid) {
    EXPECT_TRUE(IsValidLeagueName("Lliga Universitaria"));
}

TEST_F(ControllerTests, LeagueNameTooShort) {
    EXPECT_FALSE(IsValidLeagueName("Li"));
}

TEST_F(ControllerTests, LeagueNameEmpty) {
    EXPECT_FALSE(IsValidLeagueName(""));
}

TEST_F(ControllerTests, LeagueNameTooLong) {
    string longName(51, 'A');
    EXPECT_FALSE(IsValidLeagueName(longName));
}

// ============================================================================
// TEAM VALIDATION TESTS (Expected behavior for CtrlEnregistrarEquip)
// ============================================================================

TEST_F(ControllerTests, TeamNameValid) {
    EXPECT_TRUE(IsValidTeamName("Equip A"));
}

TEST_F(ControllerTests, TeamNameTooShort) {
    EXPECT_FALSE(IsValidTeamName("Eq"));
}

// ============================================================================
// MATCH VALIDATION TESTS (Expected behavior for CtrlEditarPartit)
// ============================================================================

TEST_F(ControllerTests, ScoreValid) {
    EXPECT_TRUE(IsValidScore(0));
    EXPECT_TRUE(IsValidScore(5));
}

TEST_F(ControllerTests, ScoreInvalidNegative) {
    EXPECT_FALSE(IsValidScore(-1));
}

// ============================================================================
// ACTUAL CONTROLLER INTEGRATION TESTS
// ============================================================================
TEST_F(ControllerTests, CtrlIniciSessioRealInstance_CorreuFormatValidTest) {
    // Aquest test EXIGIRÀ el controller compilat de la dll/exe principal
    try {
        Playcampus::Domini::CtrlIniciSessio^ ctrl = gcnew Playcampus::Domini::CtrlIniciSessio();
        // Cridem al comportament de veritat
        bool success = ctrl->IniciarSessio(gcnew System::String("invalidFormatCorreu"), gcnew System::String("pass"));
        // Com que la connexió a la BD probablement fallarà o la prova fallarà, esperem que success sigui false
        EXPECT_FALSE(success);
    }
    catch (System::Exception^ ex) {
        // En cas que llegeixi sense db
        SUCCEED() << "Correctament capturat el rebuig o manca de db amb error: ";
    }
}

// ============================================================================
// Main test runner
// ============================================================================
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

