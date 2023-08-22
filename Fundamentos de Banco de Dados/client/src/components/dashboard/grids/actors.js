import { useState, useEffect } from "react";
import { useLocation, useNavigate } from 'react-router-dom';
import axios from "axios";

import ActorsOptions from '../options/actors'

export default function ActorsGrid()
{
  const [actors, setActors] = useState([]);
  const navigate = useNavigate();

  const location = useLocation();
  const queryParams = new URLSearchParams(location.search);

  let page = Number(queryParams.get('page'));
  if (page === 0 || isNaN(page)) page = 1;

  const formatter = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD' });

  useEffect(() => 
  {
    axios.get(`http://localhost:9000${location.pathname}?${queryParams.toString()}`)
      .then(res => {setActors(res.data)})
      .catch(err => {console.log(err)})
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

  function ActorMovieList({ actor })
  {
    return (
      actor.movies.map(movie => 
      {
        return (
          <div className="artist__movie" key={ movie.title }>
            <div>{ movie.rating } </div>
            <div>{ movie.title }</div>
          </div>
        )
      })
    )
  }

  function ActorDirectorList({ actor })
  {
    return (
      actor.directors.map(director => 
      {
        return (
          <div className="artist__movie" key={ director.name }>
            <div>{ director.amount } </div>
            <div>{ director.name }</div>
          </div>
        )
      })
    )
  }

  function ActorCell({ actor })
  {
    return (
      <div className="artist">
        <div className="artist__name">Name: { actor?.actorName ? actor?.actorName : 'unknown' }</div>
        <div className="artist__dateOfBirth">Date of birth: { actor?.dateOfBirth ? actor?.dateOfBirth : 'unknown' }</div>
        <div className="artist__ethnicity">Ethnicity: { actor?.ethnicity ? actor?.ethnicity : 'unknown' }</div>
        <div className="artist__gender">Gender: { actor?.actorSex ? actor?.actorSex : 'unknown' }</div>
        <div className="artist__height">Height: { actor?.height ? `${actor?.height}cm` : 'unknown' }</div>
        <div className="artist__networth">Net worth: { actor?.netWorth ? formatter.format(actor?.netWorth) : 'unknown' }</div>
        
        {/*<div className="artist__movies">
          <p>Best rated movies: </p>
          <div>
            <ActorMovieList/>
          </div>
        </div>
        
        <div className="artist__movies">
          <p>Most director collaborations: </p>
          <div>
            <ActorDirectorList/>
          </div>
        </div>*/}
      </div>
    )
  }

  return (
    <>
      <ActorsOptions/>
      <div className="artists__wrapper">
        <div className="artists">
          { actors?.map(actor => { return <ActorCell actor={ actor } key={ actor.actorID }/> }) }
        </div>
        
        <div className='page-btns'>
          <div className='btn prev' onClick={ () => {updatePage('prev')} }>PREVIOUS</div>
          <div className='btn next' onClick={ () => {updatePage('next')} }>NEXT</div>
        </div>
      </div>
    </>
  )
}