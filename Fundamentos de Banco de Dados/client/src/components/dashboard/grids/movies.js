import React, { useEffect, useState, } from 'react';
import { Link, useLocation, useNavigate } from 'react-router-dom';
import axios from 'axios';

import MoviesOptions from '../options/movies';

export default function MoviesGrid()
{
  const location = useLocation();
  const queryParams = new URLSearchParams(location.search);
  
  let page = Number(queryParams.get('page'));
  if (page === 0 || isNaN(page)) page = 1;

  const [movies, setMovies] = useState([])
  const navigate = useNavigate();

  useEffect(() => 
  {
    axios.get(`http://localhost:9000${location.pathname}?${queryParams.toString()}`)
    .then(res => {setMovies(res.data)} )
    .catch(err => console.log(err))

  }, [page, location])

  function updatePage(direction) 
  {
    if (direction === 'next') 
    {
      const nextPage = page + 1;
      queryParams.set('page', nextPage)
      const newUrl = `${location.pathname}?${queryParams.toString()}`;

      navigate(newUrl);
      window.scrollTo(0, 0);
    } 
    
    else if (direction === 'prev' && page !== 1) 
    {
      const prevPage = page - 1;
      queryParams.set('page', prevPage)
      const newUrl = `${location.pathname}?${queryParams.toString()}`;

      navigate(newUrl);
      window.scrollTo(0, 0);
    }
  }

  function MovieCell({ movie })
  {
    return (
      <div className="movie">
        <Link to={`/movie?id=${movie.movieId}`}>
          <img className="movie__poster" src={ movie.poster } alt=""/>
        </Link>

        <div className="movie__data">
          <div className="movie__title">{ movie.title ? movie.title : 'unknown' }</div>
          <div className="movie__director">{ movie.directorName ? movie.directorName : 'unknown' }</div>
          <div className="movie__release">{ movie.releasedYear ? movie.releasedYear : 'unknown' }</div>
          <div className="movie__rating">{ movie.IMDBRating ? movie.IMDBRating : 'unknown' }</div>
        </div>
      </div>
    )
  }

  return (
    <>
      <MoviesOptions/>
      <div className='movies__wrapper'>
        <div className="movies">
          { movies.map(movie => { return <MovieCell movie={ movie } key={ movie.movieId }/> }) }
        </div>

        <div className='page-btns'>
          <div className='btn prev' onClick={ () => {updatePage('prev')} }>PREVIOUS</div>
          <div className='btn next' onClick={ () => {updatePage('next')} }>NEXT</div>
        </div>
      </div>
    </>
  )
}