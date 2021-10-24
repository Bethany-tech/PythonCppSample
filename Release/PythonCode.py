# Calculate item totals in a text file.
#  Returns item totals in dictionary
def CalculateItemTotals(filename):
    # Read purchased items from file
    f = open(filename, 'r')
    items = f.readlines()
    f.close()

    # Collate items and store their counts
    item_counts = {}
    for item in items:
        formatted_item = item.rstrip('\n')

        if formatted_item in item_counts:
            item_counts[formatted_item] += 1
        else:
            item_counts[formatted_item] = 1

    return item_counts

# Calculate and print item totals from a given text file.
def CalculateAndPrintItemTotals(filename):
    item_counts = CalculateItemTotals(filename)

    # Print item counts
    for item in item_counts:
        print(f'{item}: {item_counts[item]}')

# Calculate the frequency of a single item (itemname) from
#  a given text file (filename).
#    Returns frequency of item or zero of item not found.
def CalculateSingleItemFrequency(filename, itemname):
    item_counts = CalculateItemTotals(filename)

    # Retrieve item frequency if it exists
    if itemname in item_counts:
        return item_counts[itemname]
    return 0

# Calculate item totals from a given file (filename) and
#  output those totals to another file (outfilename).
def CalculateAndSaveItemTotals(filename, outfilename):
    item_counts = CalculateItemTotals(filename)

    # Create item total lists as a string.
    item_totals = []
    for item in item_counts:
        item_totals.append(f'{item} {item_counts[item]}\n')

    # Write item total strings to file.
    f = open(outfilename, 'w')
    f.writelines(item_totals)
    f.close()
