<h2>Project Title : Identfying objects via vertices</h2>
Project Members: <a href="https://github.com/furkancaglayan">Furkan Çağlayan</a> & <a href="https://github.com/EmreOzkose">Yunus Emre Özköse</a>

<h3>Introduction </h3>
In this project, we will create an application to recognize 3D shapes and distinguish them from one another. Basically, a scene will be created of different object types such as humans and cars. In this scene, as objects passing through camera view, they will be identified and labeled, again as a human or a car.

<img src="images/introfigure.png">

<br>

In detail, project can be divided as computer graphics and learning part. In the graphics part, a scene will be created and some models such as human, car, wolf etc. will be modeled and placed to the created scene. While creating that scene, a hierarchy will be created and the scene will be designed according to that hierarchy. In learning part, a machine learning algorithm which is called neural networks will be used. Since vertex attributes of the objects are critical for an object, it would be informative. Neural networks will be taken flattened vertices as an input and give class probabilities as an output. Features will be normalized for handling scaling problem. The main problem in learning is dataset. We will handle this problem with procedural mesh generation. This method will be used to create a different object of the same type from an object. In this way, many vertex samples will be created, will be flattened and a dataset will be created. After that, the designed model will be trained and parameters will be fine-tuned. 

Scene will be controlled through a user interface system. For example, we will be able to do:
<ul>
    <li> We will be able to select, identify or create new deformed objects. </li>
    <li> Change lightning attributes such as intensity and color.</li>
    <li> Change viewing, for example, switch between orthographic or perspective viewing, change a field of view</li>
    <li> Switch between flat and smooth shading models.</li>
</ul>
