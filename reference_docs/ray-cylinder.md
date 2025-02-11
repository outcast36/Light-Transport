# Ray-Cylinder Intersection

## Definitions: 
Parametric representation of a line in 3D: $f(t) = \vec{p} + t\vec{d}$ 

Implicit representation of a cylinder centered about the line containing the point $\vec{a}$, parallel to the unit direction vector $\vec{n}$, and with radius $r$:

$||((\vec{x} - \vec{a}) - ((\vec{x} - \vec{a}) \cdot \vec{n})\vec{n})||^2 = r^2$

The projection of the vector $\vec{u}$ in the direction of the unit vector $\vec{n}$ is defined as 

$\vec{u_{proj}} = (\vec{u} \cdot \vec{n}) \vec{n}$

## Intersection
Substitute implicit ray definition in as $\vec{x}$ in the cylinder equation. The length of the intersection point's projection to the
cylinder's axis of rotation should be equal to the cylinder's radius.  The final quadratic equation for $t$ is similar to the one seen with spheres. Cylinders contain an additional term substracted from the squared magnitude of the intersection to the given point $\vec{a}$. Subtracted from the sphere term is the projection length of the vector from the intersection point to the cylinder axis. The quadratic equation for $t$:
\begin{center}
$||\vec{p} + t\vec{d} - \vec{a}||^2 - (\vec{n} \cdot (\vec{p} + t\vec{d} - \vec{a}))^2 = r^2$
\end{center}

The coefficients of the regular form:
\begin{center}
    $A = (\vec{d} \cdot \vec{d}) - (\vec{n} \cdot \vec{d})^2$

    $B = 2((\vec{d} \cdot (\vec{p} - \vec{a})) - (\vec{n} \cdot \vec{d})(\vec{n} \cdot (\vec{p} - \vec{a})))$

    $C = (\vec{p} - \vec{a}) \cdot (\vec{p} - \vec{a}) - (\vec{n} \cdot (\vec{p} - \vec{a}))^2 - r^2$
\end{center} 

## Full Derivation
See ```ray-sphere.md``` for full derivation on the first term of the cylinder form. 
