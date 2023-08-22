import { useState, useEffect } from "react";
import { useLocation, useNavigate } from 'react-router-dom';
import DirectorsOptions from '../options/directors';
import axios from "axios";

export default function DirectorsGrid()
{
  const [directors, setDirectors] = useState([]);
  const navigate = useNavigate();

  const location = useLocation();
  const queryParams = new URLSearchParams(location.search);

  let page = Number(queryParams.get('page'));
  if (page === 0 || isNaN(page)) page = 1;

  useEffect(() => 
  {
    axios.get(`http://localhost:9000${location.pathname}?${queryParams.toString()}`)
      .then(res => {setDirectors(res.data)})
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

  
  /*function DirectorMovieList()
  {
    return (
      director.movies.map(movie => 
      {
        return (
          <div className="artist__movie" key={ movie.title }>
            <div>{ movie.rating } </div>
            <div>{ movie.title }</div>
          </div>
        )
      })
    )
  }*/

  /*function DirectorActorList()
  {
    return (
      director.actors.map(actor => 
      {
        return (
          <div className="artist__movie" key={ actor.name }>
            <div>{ actor.amount } </div>
            <div>{ actor.name }</div>
          </div>
        )
      })
    )
  }*/

  function DirectorCell({ director })
  {
    let sex = '';

    switch(director.directorSex)
    {
      case 'M': sex = 'Male'; break;
      case 'F': sex = 'Female'; break;
      default: sex = 'unknown'; break;
    }

    return (
      <div className="artist">
        <div className="artist__name">Name: { director?.directorName }</div>
        
        <div className="artist__sex">Sex: { sex }</div>

        <div className="artist__total-movies"> Total movies: { director?.qnt_filme }</div>
        
        {/*<div className="artist__movies">
          <p>Best rated movies: </p>
          <div>
            <DirectorMovieList/>
          </div>
        </div>
        
        <div className="artist__movies">
          <p>Most actor collaborations: </p>
          <div>
            <DirectorActorList/>
          </div>
        </div>*/}
      </div>
    )
  }

  return (
    <>
      <DirectorsOptions/>
      <div className="artists__wrapper">
      
        <div className="artists">
        { directors?.map(director => { return <DirectorCell director={ director } key={ director.directorId }/> }) }
        </div>

        <div className='page-btns'>
          <div className='btn prev' onClick={ () => {updatePage('prev')} }>PREVIOUS</div>
          <div className='btn next' onClick={ () => {updatePage('next')} }>NEXT</div>
        </div>
      </div>
    </>
  )
}