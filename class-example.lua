BankAccount = {
    number = 0,
    holder_name = "",
    balance = 0.0
}

function BankAccount:deposit(amount)
    self.balance = self.balance + amount
end

function BankAccount:withdraw(amount)
    self.balance = self.balance - amount
end

function BankAccount:new(t)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    return t
end


-----------------------------------------------------
-----------------------------------------------------
jean_account = BankAccount:new({
    number = 123456,
    holder_name = "Jean Dupont"
})

jean_account:deposit(500)
jean_account.balance = 3 -- :|

print(jean_account.balance)
