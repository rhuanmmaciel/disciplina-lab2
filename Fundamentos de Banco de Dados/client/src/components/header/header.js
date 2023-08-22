import { Link } from 'react-router-dom';

export default function Header()
{
  return (
    <div className="header">
      <ul className="header__list">
        <Link to='/movies'><li className="header__item">Movies</li></Link>
        <Link to='/directors'><li className="header__item">Directors</li></Link>
        <Link to='/actors'><li className="header__item">Actors</li></Link>
        <Link to='/charts'><li className="header__item">Charts</li></Link>
      </ul>
    </div>
  )
}