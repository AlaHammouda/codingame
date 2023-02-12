stock_values = []
maximum_loss = -1

n = int(input())
for i in input().split():
    stock_values.append(int(i))

for t in range(n):
    if maximum_loss < stock_values[t]:
        for tn in range(t + 1, n):
            current_loss = stock_values[t] - stock_values[tn]
            if current_loss > maximum_loss:
                maximum_loss = current_loss

print(0 if maximum_loss is -1 else -maximum_loss)
