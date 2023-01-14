import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.Map.Entry;
/**
 * The Main class implements an application that reads lines from the standard input
 * and prints them to the standard output.
 */
public class Main {
  /**
   * Iterate through each line of input.
   */
  public static void main(String[] args) throws IOException {
    InputStreamReader reader = new InputStreamReader(System.in, StandardCharsets.UTF_8);
    BufferedReader in = new BufferedReader(reader);
    String line;
    Map<String, String> m = new HashMap<>();
    String temp;
    String from, to;
    int iF, iT;
    int i = 0;
    while ((line = in.readLine()) != null) {
      //System.out.println(line);
      if(i == 0) temp = line;
      else if(i == 1) from = line;
      else if(i == 2) to = line;
      i++;
    }
    String[] s = temp.split(";");
    Node[] Nfrom = new Node[s.length];
    Node[] Nto = new Node[s.length];
    double[] XRate = new double[s.length];
    Graph fGraph = new Graph();
    int index = 0;
    for(String j : s) {
      String[] tmp = j.split(",");
      Nfrom[index] = new Node(tmp[0]);
      Nto[index] = new Node(tmp[1]);
      XRate[index] = Double.parseDouble(tmp[2]);
      if(from.equals(Nfrom[index].getName())) {
        iF = index;
      }
      if(to.equals(Nto[index].getName())) {
        iT = index;
      }
      Nfrom[index].addDes(Nto[index], XRate[index]);
      fGraph.addN(Nfrom[index]);
      fGraph.addN(Nto[index]);
      index++;
    }
    fGraph = MaxPathFromStart(fGraph, Nfrom[iF]);
  }
  /** Graph of currency
  */
  public class Graph {
    private Set<Node> set = new HashSet<>();
    public void addN(Node n) {
      set.add(n);
    }
  }
  
  public class Node {
    private String name;
    private Double Xrate = Double.MAX_VALUE;
    private List<Node> maxPath = new LinkedList<>();
    Map<Node, Double> neighbor = new HashMap<>();
    public void addDes(Node des, double d) {
      neighbor.put(des, d);
    }
    public Node(String n) {
      name = n;
    }
    public void setDis(double d) {
      Xrate = d;
    }
    public double getDis() {
      return Xrate;
    }
    public Map<Node, Double> getNeighbor() {
      return neighbor;
    }
    public List<Node> getMaxPath() {
      return maxPath;
    }
    public void setMaxPath(List<Node> maxPath) {
      this.maxPath = maxPath;
    }
    public String getName() {
      return name;
    }
  }
  
  public static Graph MaxPathFromStart(Graph g, Node start) {
    start.setDis(0);
    Set<Node> settledN = new HashSet<>();
    Set<Node> unsettledN = new HashSet<>();
    unsettledN.add(start);
    while(unsettledN.size() != 0) {
      Node curr = LongestN(unsettledN);
      unsettledN.remove(curr);
      for(Entry<Node, Double> pair : curr.getNeighbor().entrySet()) {
        Node n = pair.getKey();
        Double edgeWeight = pair.getValue();
        if(!settledN.contains(n)) {
          computeMaxDistance(n, edgeWeight, curr);
          unsettledN.add(n);
        }
      }
      settledN.add(curr);
    }
    return g;
  }
  
  private static Node LongestN(Set<Node> unsettledN) {
    Node maxN = null;
    double MaxDis = Double.MAX_VALUE;
    for(Node n : unsettledN) {
      double d = n.getDis();
      if(d < MaxDis) {
        MaxDis = d;
        maxN = n;
      }
    }
    return maxN;
  }
  
  private static void computeMaxDistance(Node n, Double edgeWeight, Node start) {
    Double d = start.getDis();
    if(d+edgeWeight < n.getDis()) {
      n.setDis(d+edgeWeight);
      LinkedList<Node> maxPath = new LinkedList<> (start.getMaxPath());
      maxPath.add(start);
      n.setMaxPath(maxPath);
    }
  }
}
