import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn import tree
import matplotlib.pyplot as plt

df = pd.read_csv('Flex_ultrasonic_data_labeled.csv')

X = df[['Flex', 'difference']]
y = df['label']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

dt_classifier = DecisionTreeClassifier(max_depth=3, random_state=42)
dt_classifier.fit(X_train, y_train)

y_pred = dt_classifier.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy:.2f}")
print("\nClassification Report:")
print(classification_report(y_test, y_pred))
print("\nConfusion Matrix:")
print(confusion_matrix(y_test, y_pred))

plt.figure(figsize=(30,10))
tree.plot_tree(dt_classifier,
               feature_names=X.columns,
               class_names=['0', '1'],
               filled=True,
               rounded=True)
plt.title("Decision Tree for Flex Ultrasonic Data")
plt.savefig('decision_tree.png')
plt.show()