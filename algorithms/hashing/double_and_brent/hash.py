class HashEntry:
    """
    Wrapper class for hash table entries.
    """
    def __init__(self, key: int, value: object) -> None:
        """
        Constructor for hash table entries.
        :param key: key of hash table entry
        :param value: value of hash table entry
        :return: None
        """
        self.key = key
        self.value = value

    def delete(self) -> None:
        """
        Delete the hash table entry content.
        :return: None
        """
        self.key = None
        self.value = None

    def __str__(self) -> str:
        """
        The string representation for the object is the string representation of the key.
        :return: String representation of key
        """
        return f"{self.key}"


class HashTable:
    """
    Implementation of a hash table based on Open Hashing.
    A hash entries is wrapped in a HashEntry object before being put into the list that represents the hash table:
    -  If the hash table entry is None, the entry is empty
    -  If the hash table contains a HashEntry wrapper object with a None key and value attributes, the entry is "free",
      meaning there was data that has already been deleted
    -  If the hash table contains a HashEntry wrapper object with a valid key and value attributes, the hash table entry
      is in use
    Attributes:
        table: list of HashEntry or None objects
    """
    table: []

    def __init__(self, size: int):
        """
        Initialize a hash table with a given size.
        :param size: hash table size, maximum number of elements that may be stored in the hash table
        :return: None
        """
        self.table = [None] * size
        self.m = size

    def insert(self, key: int, value: object) -> int:
        """
        Insert the given key/value entry into the hash table using double hashing (without Brent).
        :param key: the key that identifies the entry and that is used for the hash function
        :param value: value to insert with the key into the hash table
        :return: table index where the value was successfully inserted, or -1 if table is full or an entry with the
        same key already exists within the table
        """
        # Begin implementation
        # print("")
        # print(f"---------- insert called with {key} and {value} {self.m}")

        i = self.calculate_hash(key, self.m)

        # self.print_table()

        # check if position is already taken
        if self.is_free(i):
            # print(f"outer position {i} is free, will insert {key}:{value}")
            self.set_key_value(i, key, value)
            return i

        if self.table[i].key == key:
            return -1

        j = self.calculate_double_hash(key, self.m)

        for l in range(1, self.m):
            pos = self.modulo_Euclidean(i - (l * j), self.m)
            # print(f"check for freenes {pos}")
            if (self.is_free(pos)):
                # print(f"inner position {pos} is free, will insert {key}:{value}")
                self.set_key_value(pos, key, value)
                return pos

            if self.table[pos].key == key:
                return -1

        # print(f"cannot find position for {key}:{value}")
        return -1
        # End implementation

    def insert_brent(self, key: int, value: object) -> int:
        """
        Insert a given key/value entry into the hash table using double hashing with Brent.
        :param key: the key that identifies the entry and that is used for the hash function
        :param value: value to insert with the key into the hash table
        :return: table index where the object was successfully inserted, or -1 if table is full or an entry with the
        same key already exists within the table
        """
        # Begin implementation

        # print("")
        # print(f"insert_brent called with {key} and {value}")

        i = self.calculate_hash(key, self.m)

        # check if position is already taken
        if (self.is_free(i)):
            # print(f"position {i} is free, will insert {key}:{value}")
            self.set_key_value(i, key, value)
            return i

        # position is already taken, use brent
        return self.brents_algorithm(key, value, self.m)
        # End implementation

    def retrieve(self, key: int) -> object:
        """
        Retrieve the key in the hash table and return the value object.
        :param key: the key that identifying the entry
        :return: value object if the was found in the hash table, None otherwise
        """
        # Begin implementation
        # print("")
        # print(f"------------- search for {key}")

        # self.print_table()

        pos = -1
        cycle_detection = -15

        # look for key in first possible place
        pos = self.calculate_hash(key, self.m)
        # print(f"looking for {key} on {pos}")
        if self.table[pos].key == key:
            # key found returning
            return self.table[pos].value

        # print(f"[k:{key}] not found in first possible [pos:{pos}], continue search ..")

        while (1):
            if cycle_detection == -15:
                cycle_detection = pos
            elif cycle_detection == pos:
                # print(f"cycle detected, erroring out")
                return None

            altpos = self.modulo_Euclidean((pos - self.calculate_double_hash(key, self.m)), self.m);
            if self.table[altpos] and self.table[altpos].key == key:
                # key found returning
                return self.table[altpos].value

            # print(f"[k:{key}] not found on [altpos:{altpos}], continue search ..")

            pos = altpos

        # search without success - never reached
        return None
        # End implementation

    def delete(self, key: int) -> int:
        """
        Delete an entry from the hash table.
        :param key: key identifying the hash table entry
        :return: table index where the key was found and deleted, or -1 if the key was not found
        """
        # Begin implementation
        # print(f"----------- delete {key}")
        # self.print_table()

        pos = -1
        cycle_detection = -15

        # look for key in first possible place
        pos = self.calculate_hash(key, self.m)
        # print(f"looking for {key} on {pos}")
        if self.table[pos].key == key:
            self.table[pos].key = None
            self.table[pos].value = None
            # self.print_table()
            # print(f"will return {pos}")
            return pos

        # print(f"[k:{key}] not found in first possible [pos:{pos}], continue search ..")

        while (1):
            if cycle_detection == -15:
                cycle_detection = pos
            elif cycle_detection == pos:
                # print(f"cycle detected, erroring out")
                return -1

            altpos = self.modulo_Euclidean((pos - self.calculate_double_hash(key, self.m)), self.m);
            if self.table[altpos] and self.table[altpos].key == key:
                # print(f"key {key} found on {altpos}")
                # key found returning
                self.table[altpos].key = None
                self.table[altpos].value = None
                return altpos

            # print(f"[k:{key}] not found on [altpos:{altpos}], continue search ..")

            pos = altpos

        return -1
        # End implementation

    def set_key_value(self, index: int, key: int, value: object):
        """
        Set a key/value entry in the hash table at the given index
        :param index: index in hash table
        :param key: key to set
        :param value: value to set
        :return:
        """
        if self.is_empty(index):
            # insert new HashEntry object at position index
            self.table[index] = HashEntry(key, value)
        else:
            # re-use existing HashEntry object
            self.table[index].key = key
            self.table[index].value = value

    def is_empty(self, index: int) -> bool:
        """
        Check if a given table index is empty, i.e. it contains None instead of a HashEntry object
        @param index: index in hash table to check
        @return: True if the table contains None at the given index, False otherwise
        """
        # check if table index is empty
        if self.table[index] is None:
            return True
        else:
            return False

    def is_free(self, index: int) -> bool:
        """
        Check if a given table index is free, i.e. either empty or it contains a deleted entry
        :param index:
        :return: True if the table index may be used for inserting, False otherwise
        """
        # If table index is empty it is free
        if self.is_empty(index):
            return True
        # If it contains a deleted entry it is also free
        if self.table[index].key is None:
            return True
        else:
            return False

    # Add your auxiliary methods here
    # Begin implementation
    def brents_algorithm(self, k, v, m):
        cycle_detect = -15
        i = self.calculate_hash(k, m)

        while not self.is_free(i):
            if cycle_detect == -1:
                cycle_detect = i
            elif cycle_detect == i:
                # print("cycle detected")
                return -1

            neufolgt = self.modulo_Euclidean((i - self.calculate_double_hash(k, m)), m)
            altfolgt = self.modulo_Euclidean((i - self.calculate_double_hash(self.table[i].key, m)), m)

            # self.print_table()

            if self.is_free(neufolgt) or not self.is_free(altfolgt):
                i = neufolgt;
            else:
                self.set_key_value(altfolgt, self.table[i].key, self.table[i].value)
                self.set_key_value(i, None, self.table[i].value)
            # self.print_table()

        self.set_key_value(i, k, v)
        # self.print_table()
        return(i)

    def print_table(self):
        i = 0
        for entry in self.table:
            if entry:
                print(f"[{i}]: {entry.key}:{entry.value}")
            else:
                print(f"[{i}]: None")
            i += 1

    def calculate_hash(self, key, m):
        return self.modulo_Euclidean(key, m)

    def calculate_double_hash(self, k, m):
        return (1 + self.modulo_Euclidean(k, m - 2))

    def modulo_Euclidean(self, k, m):
        euclidean_modulo = k % m
        if euclidean_modulo < 0:
            euclidean_modulo += m
        return euclidean_modulo
    # End implementation