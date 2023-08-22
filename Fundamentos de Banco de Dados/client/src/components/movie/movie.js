import { useState, useEffect } from "react";
import { Link, useLocation } from "react-router-dom"
import axios from "axios";

export default function Movie()
{
  const [movie, setMovie] = useState(null);
  const [actors, setActors] = useState([]);

  const location = useLocation();
  const queryParams = new URLSearchParams(location.search);
  const id = queryParams.get('id');

  const formatter = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD' });
  let actorsArray = [];

  useEffect(() => 
  {
    axios.get(`http://localhost:9000/movie?idMovie=${id}`)
      .then(res => 
      {
        let actorNames = res.data[0].actorNames;
        actorsArray = actorNames.split(",");
        setActors(actorsArray);
        setMovie(res.data[0]); 
      })
      .catch(err => {console.log(err)})
  }, [id])

  function Header()
  {
    return (
      <div className="header">
        <ul className="header__list">
          <Link to="/"><li className="header__item">Home</li></Link>
        </ul>
      </div>
    )
  }

  return (
    <>
      <Header/>

      <div className="movie__wrapper">
        <div className="movie">
          <img className="movie__poster" src={movie?.poster}/>
          
          <div className="movie__data">
            <div className="movie__header">
              <h1 className="movie__title">{ movie?.title }</h1>
              <span className="movie__release">{ movie?.releasedYear } |</span>
              <span className="movie_runtime"> { movie?.runtime }min |</span>
              <span className="movie__release"> { movie?.genre }</span>
            </div>

            <div className="movie__body">
              <div className="movie__director">Director: { movie?.directorName }</div>
              <div className="movie__gross">Box office: { formatter.format(movie?.gross) }</div>
              <div className="movie__rating">IMDB Rating: { movie?.IMDBRating }</div>
            </div>

            <div className="movie__overview">
              <div style={{ marginBottom: 12 }}>Overview:</div>
              <div className="movie__text">{ movie?.overview }</div>
            </div>

            <div className="movie__cast">
              <div style={{ marginBottom: 12 }}>Most notable cast:</div>
              {
                actors.map((actor, index) => 
                (
                  <div className="movie__actor" key={index}>
                    {actor}
                  </div>
                ))
              }
              <div>{ actorsArray }</div>
            </div>
          </div>
        </div>
      </div>
    </>
  )
}