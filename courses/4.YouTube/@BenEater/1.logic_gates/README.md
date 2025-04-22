# Logic Gates

| Topic | Description |
|-|-|
| [Making logic gates from transistors](https://www.youtube.com/watch?v=sTu3LwpF6XI) | [0:00](https://www.youtube.com/watch?v=sTu3LwpF6XI) - basic transistor |
| | [2:25](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=145s) - inverter |
| | [4:14](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=254s)  - and gate |
| | [6:08](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=368s)  - or gate |
| | [7:38](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=458s)  - NO gate😀 |
| | [8:29](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=509s)  - xor gate |
| | [11:50](https://www.youtube.com/watch?v=sTu3LwpF6XI&t=710s)  - whole list |


## Buffer

### Buffer (using NPN)

- [ ] Schematic

<img src=images/s8050_bjt_switch.png width='30%' height='30%' > </img>

- [ ] Circuit

<img src=images/npn_circuit.png width='30%' height='30%' > </img>

### Buffer (using PNP)

- [ ] Circuit

<img src=images/pnp_circuit.png width='30%' height='30%' > </img>



## Inverter

### Inverter (using NPN)

<img src=images/npn_circuit2.png width='30%' height='30%' > </img>

# References

Sure! Here's a compact summary:

---

### 🔄 **NPN vs PNP Transistor**

| Feature          | **NPN**                        | **PNP**                        |
|------------------|--------------------------------|--------------------------------|
| Current flow     | Collector → Emitter            | Emitter → Collector            |
| Turns ON when    | Base **>** Emitter (~0.7V)     | Base **<** Emitter (~0.7V)     |
| Control Signal   | **Positive** to base           | **Negative** to base           |
| Typical Use      | **Low-side switch**            | **High-side switch**           |
| Symbol Arrow     | ➝ (out of emitter)             | ⬅ (into emitter)               |
| Easier for MCU   | ✅ Yes                          | ⚠️ Needs level shifting         |

---

### ⚙️ Example Circuits

- **NPN (S8050)**:  
  Load to Vcc → **collector** → emitter to GND  
  MCU gives **high** to base to turn ON.

- **PNP (S8550)**:  
  Emitter to Vcc → **collector** to load → GND  
  MCU gives **low** to base to turn ON.


