import { useRef } from "react"
import { useLocation, useNavigate } from 'react-router-dom';

export default function MoviesOptions() 
{
  const navigate = useNavigate();

  const nameRef = useRef();
  const directorRef = useRef();
  const releaseMinRef = useRef();
  const releaseMaxRef = useRef();
  const ratingMinRef = useRef();
  const ratingMaxRef = useRef();

  function sortName(order)
  {
    const newQuery = `/movies/order/name?order=${order}`;
    navigate(newQuery)
  }

  function sortRating(order)
  {
    const newQuery = `/movies/order/imdb?order=${order}`;
    navigate(newQuery)
  }

  function sortRelease(order)
  {
    const newQuery = `/movies/order/year?order=${order}`;
    navigate(newQuery);
  }

  function sortGross(order)
  {
    const newQuery = `/movies/order/gross?order=${order}`;
    navigate(newQuery);
  }

  function filterName()
  {
    const newQuery = `/movies/filter/name?title=${nameRef.current.value}`;
    navigate(newQuery);
  }

  function filterDirector()
  {
    const newQuery = `/movies/filter/director?director=${directorRef.current.value}`;
    navigate(newQuery);
  }

  function filterRelease()
  {
    const newQuery = `/movies/filter/year?ano1=${releaseMinRef.current.value}&ano2=${releaseMaxRef.current.value}`;
    navigate(newQuery);
  }

  function filterRating()
  {
    const newQuery = `/movies/filter/rating?rating1=${ratingMinRef.current.value}&rating2=${ratingMaxRef.current.value}`;
    navigate(newQuery);
  }

  function filter()
  {
    if (nameRef.current.value !== '')
      filterName();

    else if (directorRef.current.value !== '')
      filterDirector();

    else if (releaseMinRef.current.value !== '' || releaseMaxRef.current.value !== '')
    {
      if (releaseMinRef.current.value === '')
        releaseMinRef.current.value = 1919

      if (releaseMaxRef.current.value === '')
        releaseMaxRef.current.value = 2024
      
      filterRelease();
    }

    else if (ratingMinRef.current.value !== '' || ratingMaxRef.current.value !== '')
    {
      if (ratingMinRef.current.value === '')
        ratingMinRef.current.value = 8.1

      if (ratingMaxRef.current.value === '')
        ratingMaxRef.current.value = 10
      
      filterRating();
    }
  }

  return (
    <div className="options">
      <div className="options__sort">
        <div className="options__sort--title">SORT</div>
        <div className="options__sort__list">
          <div className="options__sort--name">
            <div className="option" onClick={ () => {sortName('ASC')} }>Name (A-Z)</div>
            <div className="option" onClick={ () => {sortName('DESC')} }>Name (Z-A)</div>
          </div>

          <div className="options__sort--rating">
            <div className="option" onClick={ () => {sortRating('ASC')} }>Rating Ascending</div>
            <div className="option" onClick={ () => {sortRating('DESC')} }>Rating Descending</div>
          </div>

          <div className="options__sort--release">
            <div className="option" onClick={ () => {sortRelease('ASC')} }>Release Ascending</div>
            <div className="option" onClick={ () => {sortRelease('DESC')} }>Release Descending</div>
          </div>

          <div className="options__sort--gross">
            <div className="option" onClick={ () => {sortGross('ASC')} }>Box office Ascending</div>
            <div className="option" onClick={ () => {sortGross('DESC')} }>Box office Descending</div>
          </div>
        </div>
      </div>

      <div className="options__filter">
        <div className="options__filter--title">FILTER</div>
        <div className="options__filter__list">
          <div className="options__filter--name">
            <div className="option">Name</div>
            <input className="option--input" ref={ nameRef } type="text" name="name" id="name"/>
          </div>

          <div className="options__filter--director">
            <div className="option">Director</div>
            <input className="option--input" ref={ directorRef } type="text" name="director" id="director"/>
          </div>

          <div className="options__filter--release">
            <div className="option">Release year</div>
            <input className="option--input" ref={ releaseMinRef } type="number" name="release_from" id="release_from" placeholder="from"/>
            <input className="option--input" ref={ releaseMaxRef } type="number" name="release_to" id="release_to" placeholder="to"/>
          </div>

          <div className="options__filter--rating">
            <div className="option">Rating</div>
            <input className="option--input" ref={ ratingMinRef } type="number" name="rating_from" id="rating_from" placeholder="from"/>
            <input className="option--input" ref={ ratingMaxRef } type="number" name="rating_to" id="rating_to" placeholder="to"/>
          </div>
        </div>
      </div>

      <div className="options__submit" onClick={ filter }>SEARCH</div>
    </div>
  )
}