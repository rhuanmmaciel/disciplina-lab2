import { useRef } from "react"
import { useLocation, useNavigate } from 'react-router-dom';

export default function DirectorsOptions() 
{
  const navigate = useNavigate();

  const nameRef = useRef();
  const genderMaleRef = useRef();
  const genderFemaleRef = useRef();

  function sortName(order)
  {
    const newQuery = `/directors/order/name?order=${order}`;
    navigate(newQuery)
  }

  function sortMovies(order)
  {
    const newQuery = `/directors/order/movies?order=${order}`;
    navigate(newQuery)
  }

  function filterName()
  {
    const newQuery = `/directors/filter/name?name=${nameRef.current.value}`;
    navigate(newQuery);
  }

  function filterGender(gender)
  {
    const newQuery = `/directors/filter/gender?gender=${gender}`;
    navigate(newQuery);
  }

  function filter()
  {
    if (nameRef.current.value !== '')
      filterName();

    else if (genderMaleRef.current.checked)
      filterGender(genderMaleRef.current.value)

    else if (genderFemaleRef.current.checked)
      filterGender(genderFemaleRef.current.value)
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

          <div className="options__sort--movies">
            <div className="option" onClick={ () => {sortMovies('ASC')} }>Movies Ascending</div>
            <div className="option" onClick={ () => {sortMovies('DESC')} }>Movies Descending</div>
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

          <div className="options__filter--gender">
            <div className="option">Gender</div>
            <label className="radio"><input ref={ genderMaleRef } type="radio" name="gender" value="M"/>Male</label>
            <label className="radio"><input ref={ genderFemaleRef } type="radio" name="gender" value="F"/>Female</label>
          </div>
        </div>
      </div>

      <div className="options__submit" onClick={ filter }>SEARCH</div>
    </div>
  )
}