import pymomodb

datastore = pymomodb.PyDataStore()
datastore.put("key1", "value1")
datastore.put("key2", "value2")

print("Value for key1:", datastore.get("key1"))
print("Value for key2:", datastore.get("key2"))

datastore.delete("key1")

print("Value for key1 after deletion:", datastore.get("key1"))
