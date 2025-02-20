# Ray-Cone Intersection

## Definitions
Parametric representation of a line in 3D: $f(t) = \vec{p} + t\vec{d}$ 

Implicit representation of a cone as a surface of revolution with apex $\vec{a}$, 
parallel to the unit direction vector $\vec{n}$, and with angle $\theta$: 
\begin{center}
$||\vec{x} - \vec{a}||\cos{\theta} = \vec{n} \cdot (\vec{x} - \vec{a})$
\end{center}

This defines two half-cones on either side of the apex point which extend in both the positive and negative $\vec{n}$ direction. For rendering purposes,
a single half cone can be taken by only considering a point $\vec{x}$ to be intersecting the desired cone depending on the sign of the dot product between the cone's axis of rotation and the vector from intersection point to the apex. 

## Notation
* $(\cos{\theta})^2 = \cos^2{\theta}$

## Intersection
Substitute implicit ray definition in as $\vec{x}$ in the cone equation. 
\begin{center} 
    $||\vec{p} + t\vec{d} - \vec{a}||\cos{\theta} = \vec{n} \cdot (\vec{p} + t\vec{d} - \vec{a})$
\end{center}
This equation is similar to both the sphere and the cylinder representations if everything is squared. The squared magnitude of the intersection point to the cone's apex is scaled by a factor of $\cos^2{\theta}$ and the squared length of the projection onto the cone's axis is subtracted:
\begin{center}
$||\vec{p} + t\vec{d} - \vec{a}||^2\cos^2{\theta} - (\vec{n} \cdot (\vec{p} + t\vec{d} - \vec{a}))^2 = 0$
\end{center}
This simplifies to a quadratic equation that can be solved for t to determine if a given ray intersects the half-cone.

The coefficients of the regular form:
\begin{center}
    $A = (\vec{d} \cdot \vec{d})\cos^2{\theta} - (\vec{n} \cdot \vec{d})^2$

    $B = 2((\vec{d} \cdot (\vec{p} - \vec{a}))\cos^2{\theta} - (\vec{n} \cdot \vec{d})(\vec{n} \cdot (\vec{p} - \vec{a})))$

    $C = ||\vec{p} - \vec{a}||^2\cos^2{\theta} - (\vec{n} \cdot (\vec{p} - \vec{a}))^2$ 
\end{center} 

\newpage

## Surface Normal
Parallel to the gradient of the cone at each $\vec{x}$. Let 
\begin{center}
    $f(\vec{x}) : \mathbb{R}^3 \Rightarrow \mathbb{R} = \vec{n} \cdot (\vec{x} - \vec{a}) - \cos{\theta}||\vec{x} - \vec{a}|| = 0$. 
\end{center}
Differentiate $f$ with respect to $\vec{x}$ to get the gradient of $f$. 
\begin{center}
    $\nabla f = \vec{n} - \cos{\theta}\frac{\vec{x} - \vec{a}}{||\vec{x} - \vec{a}||}$
\end{center}
One can do the partial differentiation by components of $\vec{x}$ and form the gradient from the three partials to see that the results are equivalent. Another way to find the cone's surface normal is to consider projecting the vector $\vec{n}$ in the direction of $(\vec{x} - \vec{a})$. The surface normal is in the direction of the orthogonal component of $\vec{n}$ relative to the vector $(\vec{x} - \vec{a})$. To fact check the math, consider testing if both $\nabla f \cdot (\vec{x} - \vec{a}) = 0$ and $\nabla f \cdot \vec{n} = ||\nabla f||\sin{\theta}$.