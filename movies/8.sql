select b.name
from stars a,people b,movies c
where a.movie_id =c.id
and a.person_id= b.id
and c.title="Toy Story"