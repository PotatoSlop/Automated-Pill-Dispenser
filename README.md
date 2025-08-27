# Automated Pill Dispenser
![Alt Text](./ProjectPoster.png)
## Design Goals and Defining the Challenge
Our project sought to tackle the issue of "_Creating a device that reliably distributes, organizes, and tracks medicine for patients & caretakers_"

- Caretakers in retirement homes struggle to ensure elderly patients take their prescribed medications consistently
- Elderly individuals who frequently forget important daily tasks, such as taking pills. This is supported by data showing nearly 40% of people over 65 experience some form of memory loss, meaning independent ventures for pill dispensing becomes less reliable and potentially harmful for patients. 
- Most current solutions only show prelabeled compartments for the pills and do not provide assistance in restocking or dispensing the pills, creating greater dependence on caretakers
- Additionally, many automated solutions fail to provide accurate dosages of pills without having seperated and pre-portioned chambers which require tediuous manual refilling, especially at higher pill counts.

As such, our solution would be able to carry a week long capacity of any single pill and reduces the frequency of medication handling by 85.7% compared to standard daily pill organizers. Additionally, the carriyng capacity of the internal chamber allows for up to 40 doses before reloading, with expansion options available by taking advantage of the robust modular system. 

## Project Background
This automated pill dispenser was prototyped and designed in approximately 40 hours of total design time and programming in Northeastern's Cornerstone of Engineering 2 course, an intro course to engineering principles and design that teaches about industry software such as MATLAB, SOLIDWORKS, and ARDUINO, in addition to design and ethics associated with engineering. This project was created by a team of 4*, each delegated a role in managing the design and drafting process of our product:

- **Project Manager and Organization lead** - Landon Diakogiannakis
- **Mechanical Design and 3D Modelling** - Dylan Chen (Me)
- **Arduino and C++ Programs** - Ternence Liu
- **Electrical and Circuit Design** - John Nolan*

_*Contributed to initial circuit design, drafting phase, and aided with 3D printing process_

## Design Process and Modelling
In my role as the designer and mechanics lead, I designed the dispenser with the idea of modularity, lost-cost, and expansion in mind. The entire device is composed of 2 major parts: the upper shell, and the internal housing. This seperation of the upper and lower halves allows for easy matenence and modular upgrades/replacements: 

<img width="659" height="498" alt="image" src="https://github.com/user-attachments/assets/55f3849e-f781-4fa7-9995-249375bf7508" />


- The entire center chamber is a self-enclosed unit, allowing for designs to be implemented and adapted easily.
- For instance, if a user requires a higher dosage of a certain type of pill, the chamber can be vertically extended for greater carrying capacity.
- The mechanics center around a rotating disk powered by a hobbyist grade DC motor, with a cutout custom sized to a specific pill shape for accurate, one-by-one dosage dispensing.
    - Further iterations can be made with this modular disk design to improve the reliability of the dispensing.
    - The modular plates can have their cuttouts adjusted as well to adapt to any pill shape and size.

In order to reduce costs of production and fit our project within the development deadline, the upper shell's LCD and button interface were manually installed via a cutout extruded by hand. This also has the side effect of customization with the design, allowing users or manufacturers to adapt the design with existing hardware and user interface displays.


