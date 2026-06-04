def add_contact(directory, first_name, last_name, number):
    if (type(first_name or last_name or number) != str) or (type(directory) != dict):
        print("Invalid input")
        return
    
    key = (last_name.title(), first_name.title())
    value = number
    if key in directory:
        print(f' Contact \"{key[1]} {key[0]}\" already in system, replace {directory[key]} with {value}?\n')
        answer = input("Y/N\n")
        if answer.upper() == "Y":
            directory[key] = value
    else:
        directory[key] = value
        
def find_contact(directory, first_name, last_name):
   key = (last_name.title(), first_name.title())
   if key in directory:
       return directory[key]
   else:
       print("Contact not found")
       return None
       
def display_all(directory):
    for i in directory:
        print(f'{i[1]} {i[0]}: {directory[i]}')
    
    
PhoneBook = {}
add_contact(PhoneBook, "John", "smith", "123456789")
add_contact(PhoneBook, "john", "Smith", "9999999")
add_contact(PhoneBook, "jane", "doe", "9999999")
print(find_contact(PhoneBook,"john","smith"))
display_all(PhoneBook)