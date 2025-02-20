# Ray-Sphere Intersection

## Definitions: 
Parametric representation of a line in 3D: $f(t) = \vec{p} + t\vec{d}$ 

Implicit representation of a sphere centered at the point $\vec{c}$ and with radius $r$: $(\vec{x} - \vec{c}) \cdot (\vec{x} - \vec{c}) - r^2 = 0$

## Intersection:
Substitute $f(t) = \vec{p} + t\vec{d}$ as the point $\vec{x}$ in the sphere equation: 
\begin{center}
    $(\vec{p} + t\vec{d} - \vec{c}) \cdot (\vec{p} + t\vec{d} - \vec{c}) - r^2 = 0$
\end{center}
This substitution produces a quadratic equation of the form:
\begin{center}
    $At^2 + Bt + C = 0$
\end{center} 
where the coefficients are 
\begin{center}
    $A = (\vec{d} \cdot \vec{d})$

    $B = 2\vec{d} \cdot (\vec{p} - \vec{c})$

    $C = (\vec{p} - \vec{c}) \cdot (\vec{p} - \vec{c}) - r^2$
\end{center} 
Solve for the parameter $t$ using the quadratic formula. 
If the discriminant is less than $0.0$, then the given line does not intersect the sphere. The smaller positive solution for $t$ is the intersection point. That is,
$t_0$ is the $-$ solution and $t_1$ is the $+$ solution. 

## Full Derivation: 
$(\vec{p} + t\vec{d} - \vec{c}) \cdot (\vec{p} + t\vec{d} - \vec{c}) - r^2 = 0$

Let $\vec{u} = ((\vec{p} + t\vec{d}) - \vec{c})$. Rewrite the equation as 
\begin{center}
    $\vec{u} \cdot ((\vec{p} + t\vec{d}) - \vec{c}) - r^2 = 0$. 
\end{center}
Since the dot product is distributive, this form is equal to 
\begin{center}
    $\vec{u} \cdot (\vec{p} + t\vec{d}) - (\vec{u} \cdot \vec{c}) - r^2 = (\vec{u} \cdot \vec{p}) + (\vec{u} \cdot t\vec{d}) - (\vec{u} \cdot \vec{c}) - r^2 = 0$.
\end{center}
Undo the substitution for $\vec{u}$:
\begin{center}
    $(\vec{p} \cdot ((\vec{p} + t\vec{d}) - \vec{c})) + (t\vec{d} \cdot ((\vec{p} + t\vec{d}) - \vec{c})) - (\vec{c} \cdot ((\vec{p} + t\vec{d}) - \vec{c})) - r^2 = 0$
\end{center}
Distribute each term then rearrange into standard quadratic form: 
\begin{center}
    $(\vec{d} \cdot \vec{d})t^2 + 2((\vec{p} \cdot \vec{d}) - (\vec{d} \cdot \vec{c}))t + ((\vec{p} \cdot \vec{p}) - 2(\vec{p} \cdot \vec{c}) + (\vec{c} \cdot \vec{c}) - r^2) = 0$
\end{center}
To simplify the form of $B$, note that $\vec{d}$ appears in both terms of $B = 2((\vec{p} \cdot \vec{d}) - (\vec{d} \cdot \vec{c}))$.
$\vec{d}$ can be factored out using the distributive property of dot products. For $C$, we have something
of the form $(a+b)^2 = a^2 + 2ab + b^2$ written using dot product notation, which can be factored into:
\begin{center}
    $(\vec{p} \cdot \vec{p}) - 2(\vec{p} \cdot \vec{c}) + (\vec{c} \cdot \vec{c}) = (\vec{p} - \vec{c}) \cdot (\vec{p} - \vec{c})$.
\end{center}

## Surface Normals:
The vector normal to the sphere's surface at the intersection point $\vec{x} = \vec{p} + t\vec{d}$ is 
\begin{center}
    $\frac{1}{r}(\vec{x} - \vec{c})$
\end{center}
The gradient of the implicit function describing the sphere is:
\begin{center}
    $2(\vec{x} - \vec{c})$
\end{center}
Which has magnitude $2r$.
 
Also see: https://education.siggraph.org/static/HyperGraph/raytrace/rtinter1.htm