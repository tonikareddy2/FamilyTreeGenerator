import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

class Individual {
    private String name;
    private String birthdate;
    private ArrayList<Individual> children;

    public Individual(String name, String birthdate) {
        this.name = name;
        this.birthdate = birthdate;
        this.children = new ArrayList<>();
    }

    public void addChild(Individual child) {
        children.add(child);
    }

    public String getName() {
        return name;
    }

    public String getBirthdate() {
        return birthdate;
    }

    public ArrayList<Individual> getChildren() {
        return children;
    }
}

class FamilyTree {
    private Individual root;

    public FamilyTree(String rootName, String rootBirthdate) {
        root = new Individual(rootName, rootBirthdate);
    }

    public Individual getRoot() {
        return root;
    }

    public void addChild(Individual parent, Individual child) {
        parent.addChild(child);
    }

    public Individual searchIndividual(Individual node, String name) {
        if (node == null) return null;
        if (node.getName().equals(name)) return node;

        for (Individual child : node.getChildren()) {
            Individual found = searchIndividual(child, name);
            if (found != null) return found;
        }
        return null;
    }

    public void destroyPerson(Individual node, String name) {
        if (node == null) return;

        if (node.getName().equals(name)) {
            for (Individual child : node.getChildren()) {
                destroyPerson(child, child.getName());
            }
            root = null;
            return;
        }

        ArrayList<Individual> children = node.getChildren();
        for (int i = 0; i < children.size(); i++) {
            if (children.get(i).getName().equals(name)) {
                destroyPerson(children.get(i), name);
                children.remove(i);
                return;
            }
        }
    }

    public void visualizeTree(Individual node, int depth) {
        if (node == null) return;

        for (int i = 0; i < depth; i++) {
            System.out.print("  "); // Indentation for hierarchy
        }
        System.out.println(node.getName() + " (" + node.getBirthdate() + ")");
        
        for (Individual child : node.getChildren()) {
            visualizeTree(child, depth + 1);
        }
    }

    public void findRelationship(Individual node1, Individual node2) {
        if (node1 == null || node2 == null) {
            System.out.println("One or both persons not found in the family tree.");
            return;
        }

        for (Individual child : node1.getChildren()) {
            if (child == node2) {
                System.out.println(node1.getName() + " is the parent of " + node2.getName());
                return;
            }
        }
        for (Individual child : node2.getChildren()) {
            if (child == node1) {
                System.out.println(node2.getName() + " is the parent of " + node1.getName());
                return;
            }
        }
        System.out.println(node1.getName() + " and " + node2.getName() + " are related, but further logic can be implemented here.");
    }
}

public class FamilyTreeApp {
    private static ArrayList<FamilyTree> familyTrees = new ArrayList<>();
    private static int currentTreeIndex = 0;

    public static void main(String[] args) {
        familyTrees.add(new FamilyTree("DSA kids", "01/01/1990"));

        JFrame frame = new JFrame("Family Tree Generator");
        frame.setSize(600, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        JButton addButton = new JButton("Add Family Member");
        addButton.setBounds(10, 20, 160, 25);
        panel.add(addButton);

        JButton visualizeButton = new JButton("Visualize Family Tree");
        visualizeButton.setBounds(10, 60, 160, 25);
        panel.add(visualizeButton);

        JButton searchButton = new JButton("Search Person");
        searchButton.setBounds(10, 100, 160, 25);
        panel.add(searchButton);

        JButton destroyButton = new JButton("Destroy Person");
        destroyButton.setBounds(10, 140, 160, 25);
        panel.add(destroyButton);

        JButton selectTreeButton = new JButton("Select Family Tree");
        selectTreeButton.setBounds(10, 180, 160, 25);
        panel.add(selectTreeButton);

        JTextArea output = new JTextArea();
        output.setBounds(180, 20, 380, 300);
        panel.add(output);

        addButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String parentName = JOptionPane.showInputDialog("Enter parent's name:");
                String childName = JOptionPane.showInputDialog("Enter child's name:");
                String childBirthdate = JOptionPane.showInputDialog("Enter child's birthdate:");

                Individual parent = familyTrees.get(currentTreeIndex).searchIndividual(familyTrees.get(currentTreeIndex).getRoot(), parentName);
                if (parent != null) {
                    Individual child = new Individual(childName, childBirthdate);
                    familyTrees.get(currentTreeIndex).addChild(parent, child);
                    output.append("Family member added successfully.\n");
                } else {
                    output.append("Parent not found.\n");
                }
            }
        });

        visualizeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                output.append("Visualizing Family Tree:\n");
                familyTrees.get(currentTreeIndex).visualizeTree(familyTrees.get(currentTreeIndex).getRoot(), 0);
            }
        });

        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String name = JOptionPane.showInputDialog("Enter the name of the person to search:");
                Individual person = familyTrees.get(currentTreeIndex).searchIndividual(familyTrees.get(currentTreeIndex).getRoot(), name);
                if (person != null) {
                    output.append("Person found: " + person.getName() + " (" + person.getBirthdate() + ")\n");
                } else {
                    output.append("Person not found.\n");
                }
            }
        });

        destroyButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String name = JOptionPane.showInputDialog("Enter the name of the person to destroy:");
                familyTrees.get(currentTreeIndex).destroyPerson(familyTrees.get(currentTreeIndex).getRoot(), name);
                output.append(name + " and their subtree have been removed.\n");
            }
        });

        selectTreeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String index = JOptionPane.showInputDialog("Enter the index of the family tree to select:");
                currentTreeIndex = Integer.parseInt(index) - 1;
                output.append("Family tree " + (currentTreeIndex + 1) + " selected.\n");
            }
        });
    }
}
